//
// Created by antoniomusolino on 19/01/18.
//

#define YGL_OPENGL 1
#include "../yocto/yocto_gl.h"
using namespace ygl;

struct transform {
    vec3f constanValue = {0,0,0};
    float rotation = 0;
    vec3f axesRotation = {0,1,0};
    vec3f scale = {0,0,0};
};

struct edge {
    long indexNode;
    transform transf;
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

void add_once_node_or(node &nod, node &nod1, transform constValue, Graph *graph) {
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


void add_multi_nodes_or(node &nod, Graph *graph, vector<pair<node &, transform>> vect){
    for (auto tup : vect) {
        add_once_node_or(nod, tup.first, tup.second, graph);
    }
}

void add_multi_nodes_and(node &nod, Graph *graph, vector<pair<node &, transform>> vect) {
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

void build_roads(scene* scen, std::map<string, material*>* mapMat, Graph* graph) {

    auto stradaConPiccolaUscitaInBassoVerde = loadNode("ModelsRoads/roadTile_032.obj",scen,mapMat);
    auto stradaConUscitaGrandeInBassoVerde = loadNode("ModelsRoads/roadTile_150.obj",scen,mapMat);
    auto stradaDrittaBordiVerde = loadNode("myModel/roadTile_142.obj",scen,mapMat);
    auto stradaDrittaSenzaUnBordoVerde= loadNode("ModelsRoads/roadTile_149.obj",scen,mapMat);
    auto stradaDrittaVerdeRialzata= loadNode("ModelsRoads/roadTile_183.obj",scen,mapMat);
    auto incrocioAQuattroVerde = loadNode("ModelsRoads/roadTile_141.obj",scen,mapMat);
    auto bloccoVerdePiano = loadNode("ModelsRoads/roadTile_168.obj",scen,mapMat);

    auto stradaConPiccolaUscitaInBassoBianca = loadNode("ModelsRoads/roadTile_121.obj",scen,mapMat);
    auto incrocioAQuattroBianco = loadNode("ModelsRoads/roadTile_121.obj",scen,mapMat);
    auto stradaStrisceSenzaBianca = loadNode("ModelsRoads/roadTile_109.obj",scen,mapMat);
    auto stradaDrittaConBordiGrossiBianca = loadNode("ModelsRoads/roadTile_109.obj",scen,mapMat);
    auto stradaDrittaBianca = loadNode("myModel/roadTile_292.obj",scen,mapMat);


    auto house = graph->nodes.at(graph->nodeStart);

    auto startNode = node{};
    auto stradeDritte = node{};

    add_multi_nodes_or(startNode,graph,{
            {stradeDritte, {{}}}
    });

    auto terminal = node{};

    add_multi_nodes_or(stradeDritte, graph, {
            {stradaDrittaBianca, {{1.0f,0,0}}},
            {terminal,{}}
    });

    add_multi_nodes_or(stradaDrittaBianca,graph,{
            {stradeDritte, {}}
    });
    add_multi_nodes_or(stradaDrittaVerdeRialzata,graph,{
            {stradeDritte, {}}
    });
    add_multi_nodes_or(stradaDrittaSenzaUnBordoVerde,graph,{
            {stradeDritte, {}}
    });

    add_multi_nodes_and(stradaDrittaBianca,graph, {
            {stradeDritte,{}},
            {house,{{0,0.2,-1.0f},90.0f}}
    });


    //incrocio a quattro

    graph->nodeStart = startNode.graphPos;



}


Graph* build_graph_houses(scene* scen, std::map<string, material*>* mapMat) {
    auto graph = new Graph();
    auto startNode = node{};

    // load houses
    auto BaseConScalinata = loadNode("myModel/modularBuildings_027.obj", scen, mapMat);
    auto baseConFinestreEPortone = loadNode("myModel/modularBuildings_054.obj", scen, mapMat); //

    // piani
    auto pianoFinestre = loadNode("myModel/modularBuildings_030.obj", scen, mapMat); // Piano con due finestre
    auto pianoFinestrone = loadNode("myModel/modularBuildings_041.obj", scen, mapMat); // piano con finestrona grossa e balconcino
    auto pianoFinestreQuadrate = loadNode("myModel/modularBuildings_034.obj", scen, mapMat);
    auto pianoConBalcone = loadNode("Models/modularBuildings_042.obj", scen, mapMat);
    auto pianoConFinestreCoperte = loadNode("Models/modularBuildings_033.obj", scen, mapMat);

    // load roofs
    auto tetto = loadNode("Models/modularBuildings_044.obj", scen, mapMat);
    auto tettoConFinestra = loadNode("Models/modularBuildings_063.obj", scen, mapMat);
    auto tettoTriangolo = loadNode("Models/modularBuildings_065.obj", scen, mapMat);


    //finestre
    auto portaAdArco = loadNode("Models/modularBuildings_099.obj", scen, mapMat);



    // Variabili Contenitore
    auto basi = node{};
    auto tetti = node{};
    auto piani = node{};

    add_multi_nodes_or(basi,graph, {
            {BaseConScalinata,  {}},
            {baseConFinestreEPortone, {}},
    });

    add_multi_nodes_or(tetti, graph, {
            {tetto, {}},
            {tettoConFinestra, {{1, 0, 0}}},
            {tettoTriangolo, {}}
    });
    add_multi_nodes_or(piani, graph, {
            {pianoFinestre,  {}},
            {pianoFinestrone, {}},
            {pianoFinestreQuadrate, {}},
            {pianoConBalcone,{}}
    });

    //Metto che la variabile di start parte con una base
    add_multi_nodes_or(startNode, graph, {
            {basi,{}}
    });


    //add_multi_nodes(n, graph, { {{0,0,0},nr1},{{0,0,0},nr2} } );


    //Varaibile BaseConScalinata
    add_multi_nodes_or(BaseConScalinata, graph, {
            {piani,  {{0, 0.8, 0}}},
            {tetti, {{0, 0.8, 0}}}
    });

    //Variabili piani
    add_multi_nodes_or(pianoFinestre, graph, {
            {tetti, {{0, 0.6, 0}}},
            {piani,  {{0, 0.6, 0}}}
    });

    add_multi_nodes_or(pianoFinestrone, graph, {
            {tetti, {{0, 0.6, 0}}},
            {piani,  {{0, 0.6, 0}}}
    });

    add_multi_nodes_or(pianoFinestreQuadrate, graph, {
            {tetti, {{0, 0.6, 0}}},
            {piani,  {{0, 0.6, 0}}}
    });

    add_multi_nodes_or(pianoConBalcone, graph, {
            {tetti, {{0, 0.6, 0}}},
            {piani,  {{0, 0.6, 0}}}
    });

    // Variabile Base con finestre
    add_multi_nodes_or(baseConFinestreEPortone, graph, {
            {tetti, {{0, 0.6, 0}}},
            {piani, {{0, 0.6, 0}}}
    });


    //Inserisco la variabile startNode come nodo di partenza
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
        auto newPos = pos;
        auto framTrasl = translation_frame3f(edge.transf.constanValue);
        newPos = transform_frame(newPos,framTrasl);

        if (edge.transf.scale != vec3f{0,0,0}) {
            auto framScale = scaling_frame3f(edge.transf.scale);
            newPos = transform_frame(newPos,framScale);
        }

        if (edge.transf.rotation != 0.0f) {
            auto f = rotation_frame3f(edge.transf.axesRotation, edge.transf.rotation * pif / 180.0f);
            newPos = transform_frame(newPos,f);
            // Riposiziona l'oggetto nella posizione precedente alla rotazione
            auto reposition = translation_frame3f({0,0,length(newPos.z)});
            newPos = transform_frame(newPos,reposition);
        }
        build(scn,graph, edge.indexNode,newPos,rng);
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
    cam->frame = lookat_frame3f({-10, 4, 10}, {0, 1, 0}, {0, 1, 0});
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
    build_roads(scen,mapMat,graph);
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



