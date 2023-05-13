
#pragma once
#include"../../src/include.hpp"
using namespace std;


void ConsistencyCheck(string path_to_MFEP_config_file,
                      string ofn_root="ReproducedMagneticField.root");

void DrawMagneticField_TsukubaSolenoid(cb IronYoke, cb Coil, TCanvas* c,
                                       string path_to_MFEP_config_file);

void set_coil_miniSol();

void CreateIronYokeGeometry(double pitch, string ofn_dat);

static void draw(Bs B_target, string ofn_root);





