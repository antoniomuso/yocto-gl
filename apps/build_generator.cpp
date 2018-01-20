//
// Created by antoniomusolino on 19/01/18.
//

#define YGL_OPENGL 1
#include "../yocto/yocto_gl.h"
using namespace ygl;

enum Position {
    Left,
    Right,
    Ahead,
    Back,
    Up,
    Down
};

struct edge {
    int indexNode;
    vec3f constanValue;
};

struct node {
    bool isTerminal = false;
    vector<vector<edge>> adj;
    vector<shape*> shapes;
};

struct  Graph {
    vector<node> nodes;
    int nodeStart = 0;
};

// Add a istance on scene
void add_instance(scene* scn, const std::string& name, const frame3f& f,
                  shape* shp) {
    auto ist = new instance();
    ist->name = name;
    ist->shp = shp;
    ist->frame = f;
    scn->instances.push_back(ist);
}

// create istances of nodes
void add_node_to_scene (scene* scn, const node& nod, const frame3f& f) {
    for (auto shape : nod.shapes) {
        add_instance(scn,"Instance:" + to_string(scn->instances.size()), f,shape);
    }
}

// Create node and load it shape to scene
node loadNode(const string &filename, scene *scene,
              std::map<string, material *> *mapMat) {
    auto object = load_obj(filename);
    for (auto mat : object->materials) {
        if ((*mapMat)[mat->name] != nullptr ) continue;
        auto mater = new material();
        mater->name = mat->name;
        mater->kd = mat->kd;
        mater->ks = mat->ks;
        mater->kt = mat->kt;
        mater->kr = mat->kr;
        mater->ke = mat->ke;
        (*mapMat)[mat->name] = mater;
        scene->materials.push_back(mater);
    }
    auto nod = node{};

    for (auto obj :  object->objects) {
        for (auto mesh : get_mesh(object,*obj,false)->shapes) {

            auto sh = new shape();
            sh->name = "Shape:" + to_string(scene->shapes.size());
            sh->triangles = mesh.triangles;
            sh->texcoord = mesh.texcoord;
            sh->points = mesh.points;
            sh->pos = mesh.pos;
            sh->mat = (*mapMat)[mesh.matname];
            scene->shapes.push_back(sh);
            //Aggiungo la shape al nodo
            nod.shapes.push_back(sh);

            //add_instance(scene, sh->name, frame, sh);
        }
    }
    return nod;
}

Graph* build_graph_houses(scene* scen, std::map<string, material*>* mapMat) {
    auto graph = new Graph();

    auto startNode = node{};
    startNode.adj.push_back(vector<edge>());
    startNode.adj.push_back(vector<edge>());

    startNode.adj.push_back(vector<edge>());
    startNode.adj.push_back(vector<edge>());
    startNode.adj.push_back(vector<edge>());


    // load houses
    auto n = loadNode("Models/modularBuildings_027.obj", scen, mapMat);
    auto n1 = loadNode("Models/modularBuildings_030.obj", scen, mapMat);



    // load roofs
    auto nr1 = loadNode("Models/modularBuildings_044.obj", scen, mapMat);

    auto nr2 = loadNode("Models/modularBuildings_063.obj", scen, mapMat);

    startNode.adj.at(0).push_back(edge{1,{0,0,0}});
    startNode.adj.at(1).push_back(edge{2,{0,0,0}});

    /*
    startNode.adj.at(2).push_back(edge{2,{0,0,0}});
    startNode.adj.at(3).push_back(edge{2,{0,0,0}});
    startNode.adj.at(4).push_back(edge{2,{0,0,0}});
     */




    // load to graph
    n.adj.push_back(vector<edge>());
    n.adj.push_back(vector<edge>());
    n.adj.at(0).push_back(edge{3,{0,0.8,0}});
    n.adj.at(1).push_back(edge{2,{0,0.8,0}});

    // load to graph
    n1.adj.push_back(vector<edge>());
    n1.adj.at(0).push_back(edge{3,{0,0.6,0}});

    graph->nodes.push_back(startNode);
    graph->nodes.push_back(n);
    graph->nodes.push_back(n1);
    graph->nodes.push_back(nr1);


    return graph;

}

void build (scene* scn, Graph* graph, int inode,frame3f pos) {

    auto node = graph->nodes.at(inode);
    if (node.shapes.size() != 0) add_node_to_scene(scn,node, pos);
    if (node.adj.size() == 0 ) return ;
    srand(time(NULL));
    auto s = rand();
    print("{}\n",s);
    auto ir = s % node.adj.size();

    for (auto edge : node.adj.at(ir) ) {
        pos.o += edge.constanValue;
        build(scn,graph, edge.indexNode,pos);
    }

}






int main () {
    auto scen = new scene();

    auto mapMat = new std::map<string, material*>();
    //auto mapShape = new std::map<string, shape*>();

    // add light
    auto lshp = new shape{"light"};
    lshp->pos = {{1.4f, 8, 6}, {-1.4f, 8, 6}};
    lshp->points = {0, 1};
    auto lmat = new material{"light"};
    lmat->ke = {100, 100, 100};
    lshp->mat = lmat;

    scen->shapes.push_back(lshp);
    scen->materials.push_back(lmat);
    scen->instances.push_back(
            new instance{"light", identity_frame3f, lshp});

    // add cam
    auto cam = new camera{"cam"};
    cam->frame = lookat_frame3f({0, 4, 10}, {0, 1, 0}, {0, 1, 0});
    cam->yfov = 15 * pif / 180.f;
    cam->aspect = 16.0f / 9.0f;
    cam->aperture = 0;
    cam->focus = length(vec3f{0, 4, 10} - vec3f{0, 1, 0});
    scen->cameras.push_back(cam);

    // add floor

    auto mat = new material{"floor"};
    mat->kd = {0.2f, 0.2f, 0.2f};
    scen->materials.push_back(mat);
    auto shp = new shape{"floor"};
    shp->mat = mat;
    shp->pos = {{-20, 0, -20}, {20, 0, -20}, {20, 0, 20}, {-20, 0, 20}};
    shp->norm = {{0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0}};
    shp->texcoord = {{-10, -10}, {10, -10}, {10, 10}, {-10, 10}};
    shp->triangles = {{0, 1, 2}, {0, 2, 3}};
    scen->shapes.push_back(shp);
    scen->instances.push_back(new instance{"floor", identity_frame3f, shp});


    auto graph = build_graph_houses(scen,mapMat);
    build(scen,graph,0,identity_frame3f);
    /*
    graph.nodes.push_back(loadNode("Models/modularBuildings_010.obj", scen, mapMat));
    auto nod = loadNode("Models/modularBuildings_059.obj", scen, mapMat);
    auto nod1 = loadNode("Models/modularBuildings_060.obj", scen, mapMat);
    auto nod2 = loadNode("Models/modularBuildings_061.obj", scen, mapMat);
    add_node_to_scene(scen, &nod2, make_frame3_fromzx({0,0.6,0},{0,0,1},{1,0,0}));
     */


    save_scene("./file.obj",scen,save_options());
}



