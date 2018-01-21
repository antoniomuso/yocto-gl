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
    long indexNode;
    vec3f constanValue;
};

struct node {
    bool isTerminal = false;
    vector<vector<edge>> adj;
    vector<shape*> shapes;
    long graphPos = -1;
};

struct  Graph {
    vector<node> nodes;
    long nodeStart = -1;
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

void add_once_node_or(node &nod, node &nod1, vec3f constValue, Graph *graph) {
    if (nod1.graphPos == -1) {
        nod1.graphPos = graph->nodes.size();
        graph->nodes.push_back(nod1);
    }
    if (nod.graphPos == -1) {
        nod.graphPos = graph->nodes.size();
        graph->nodes.push_back(nod);
    }
    // prendo il nodo appena creato
    auto node = graph->nodes.at(nod.graphPos);
    auto node1 = graph->nodes.at(nod1.graphPos);

    //Inserisco un nuovo vettore di archi
    node.adj.push_back(vector<edge>());
    //Inserisco dentro il vettore di archi l'arco con il nodo da aggiungere
    node.adj.at(node.adj.size()-1).push_back(edge{node1.graphPos,constValue});

    // Mi assicuro che il nodo venga salvato
    graph->nodes.at(node.graphPos) = node;
    //nod.graphPos = node.graphPos;
    //nod1.graphPos = node1.graphPos;
}


void add_multi_nodes_or(node &nod, Graph *graph, vector<pair<node &, vec3f>> vect){
    for (auto tup : vect) {
        add_once_node_or(nod, tup.first, tup.second, graph);
    }
}

void add_multi_nodes_and(node &nod, Graph *graph, vector<pair<node &, vec3f>> vect) {
    if (nod.graphPos == -1) {
        nod.graphPos = graph->nodes.size();
        graph->nodes.push_back(nod);
    }
    auto node = graph->nodes.at(nod.graphPos);
    auto vectEdge = vector<edge>();
    for (auto pair : vect) {
        if (pair.first.graphPos == -1) {
            pair.first.graphPos = graph->nodes.size();
            graph->nodes.push_back(pair.first);
        }

        auto node1 = graph->nodes.at(pair.first.graphPos);
        vectEdge.push_back(edge{node1.graphPos,pair.second});
    }

    node.adj.push_back(vectEdge);
    graph->nodes.at(node.graphPos) = node;

}


Graph* build_graph_houses(scene* scen, std::map<string, material*>* mapMat) {
    auto graph = new Graph();
    auto startNode = node{};

    // load houses
    auto BaseConScalinata = loadNode("Models/modularBuildings_027.obj", scen, mapMat);
    auto pianoFinestre = loadNode("Models/modularBuildings_030.obj", scen, mapMat); // Piano con due finestre
    auto baseConFinestreEPortone = loadNode("Models/modularBuildings_054.obj", scen, mapMat); //
    auto pianoFinestroneBalcone = loadNode("Models/modularBuildings_041.obj", scen, mapMat); // piano con finestrona grossa e balconcino

    // load roofs
    auto tetto = loadNode("Models/modularBuildings_044.obj", scen, mapMat);
    auto tettoConFinestra = loadNode("Models/modularBuildings_063.obj", scen, mapMat);


    //finestre
    auto portaAdArco = loadNode("Models/modularBuildings_099.obj", scen, mapMat);




    //add_multi_nodes(n, graph, { {{0,0,0},nr1},{{0,0,0},nr2} } );

    add_multi_nodes_or(startNode, graph, {
            {BaseConScalinata,  {0, 0, 0}},
            {baseConFinestreEPortone, {0, 0, 0}},
    });

    add_multi_nodes_or(BaseConScalinata, graph, {
            {pianoFinestre,  {0, 0.8, 0}},
            {tetto, {0, 0.8, 0}},
            {tettoConFinestra, {1, 0.8, 0}},
            {pianoFinestroneBalcone, {0, 0.8, 0}}
    });


    add_multi_nodes_or(pianoFinestre, graph, {
            {tetto, {0, 0.6, 0}},
            {tettoConFinestra, {1, 0.6, 0}},
            {pianoFinestre,  {0, 0.6, 0}},
            {pianoFinestroneBalcone, {0, 0.6, 0}}
    });

    add_multi_nodes_or(pianoFinestroneBalcone, graph, {
            {tetto, {0, 0.6, 0}},
            {tettoConFinestra, {1, 0.6, 0}},
            {pianoFinestre,  {0, 0.6, 0}}
    });

    /*
    add_multi_nodes_and(pianoFinestre, graph, {
            {tetto, {0, 0.6, 0}},
            {portaAdArco,  {0, 0, 0}},
            {portaAdArco,  {0, 0, 0}}
    });
    add_multi_nodes_and(pianoFinestre, graph, {
            {tettoConFinestra, {1, 0.6, 0}},
            {portaAdArco,  {0, 0, 0}},
            {portaAdArco,  {0, 0, 0}}
    });
    add_multi_nodes_and(pianoFinestre, graph, {
            {pianoFinestre,  {0, 0.6, 0}},
            {portaAdArco,  {0, 0, 0}},
            {portaAdArco,  {0, 0, 0}}
    });
     */


    add_multi_nodes_or(baseConFinestreEPortone, graph, {
            {pianoFinestre,  {0, 0.6, 0}},
            {tetto, {0, 0.6, 0}},
            {tettoConFinestra, {1, 0.6, 0}},
            {pianoFinestroneBalcone, {0, 0.6, 0}}
    });


    graph->nodeStart = startNode.graphPos;
    return graph;

}

void build (scene* scn, Graph* graph, long inode,frame3f pos,rng_pcg32& rng) {

    auto node = graph->nodes.at(inode);
    if (node.shapes.size() != 0) add_node_to_scene(scn,node, pos);
    if (node.adj.size() == 0 ) return ;
    auto ir = next_rand1i(rng,node.adj.size());
    print("value gen: {} values: {} \n",ir, node.adj.size()-1);
    for (auto edge : node.adj.at(ir) ) {
        pos.o += edge.constanValue;
        build(scn,graph, edge.indexNode,pos,rng);
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

    auto rng =  init_rng(0, static_cast<uint64_t>(time(NULL)));

    build(scen,graph,graph->nodeStart,identity_frame3f,rng);
    /*
    graph.nodes.push_back(loadNode("Models/modularBuildings_010.obj", scen, mapMat));
    auto nod = loadNode("Models/modularBuildings_059.obj", scen, mapMat);
    auto nod1 = loadNode("Models/modularBuildings_060.obj", scen, mapMat);
    auto nod2 = loadNode("Models/modularBuildings_061.obj", scen, mapMat);
    add_node_to_scene(scen, &nod2, make_frame3_fromzx({0,0.6,0},{0,0,1},{1,0,0}));
     */


    save_scene("./file.obj",scen,save_options());
}



