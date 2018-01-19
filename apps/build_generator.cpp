//
// Created by antoniomusolino on 19/01/18.
//

#define YGL_OPENGL 1
#include "../yocto/yocto_gl.h"
using namespace ygl;

void add_instance(scene* scn, const std::string& name, const frame3f& f,
                  obj_shape shps,material* mat) {
    auto sh = new shape();
    sh->name = name;
    sh->triangles = shps.triangles;
    sh->texcoord = shps.texcoord;
    sh->points = shps.points;
    sh->pos = shps.pos;
    sh->mat = mat;
    scn->shapes.push_back(sh);

    auto ist = new instance();
    ist->name = name;
    ist->shp = sh;
    ist->frame = f;
    scn->instances.push_back(ist);
}


void load_and_add_to_scene (const string& filename, scene *scene) {
    auto object = load_obj(filename);

    auto map = std::map<string, material*>();

    for (auto mat : object->materials) {
        auto mater = new material();
        mater->name = mat->name;
        mater->kd = mat->kd;
        map[mat->name] = mater;
        scene->materials.push_back(mater);
    }

    for (auto obj :  object->objects) {
        for (auto mesh : get_mesh(object,*obj,false)->shapes) {

            add_instance(scene,
                         "Object:" + to_string(scene->instances.size()),
                         identity_frame3f,
                         mesh,
                         map[mesh.matname]);
        }
    }



}


int main () {
    auto scen = new scene();




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

    load_and_add_to_scene("Models/modularBuildings_010.obj",scen);

    save_scene("./file.obj",scen,save_options());
}



