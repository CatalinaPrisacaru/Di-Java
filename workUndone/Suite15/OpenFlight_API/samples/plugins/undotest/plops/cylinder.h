static polygondef CylinderPolygons [] = {
   {  0,"+0.138592,-0.497334,+1.972056|+0.368691,-0.361408,+1.972056|+0.500000,-0.128643,+1.972056|+0.497334,+0.138592,+1.972056|+0.361408,+0.368691,+1.972056|+0.128643,+0.500000,+1.972056|-0.138592,+0.497334,+1.972056|-0.368691,+0.361408,+1.972056|-0.500000,+0.128643,+1.972056|-0.497334,-0.138592,+1.972056|-0.361408,-0.368691,+1.972056|-0.128643,-0.500000,+1.972056"},
   {  1,"+0.368691,-0.361408,+0.000000|+0.368691,-0.361408,+1.972056|+0.138592,-0.497334,+1.972056|+0.138592,-0.497334,+0.000000"},
   {  1,"+0.500000,-0.128643,+0.000000|+0.500000,-0.128643,+1.972056|+0.368691,-0.361408,+1.972056|+0.368691,-0.361408,+0.000000"},
   {  1,"+0.497334,+0.138592,+0.000000|+0.497334,+0.138592,+1.972056|+0.500000,-0.128643,+1.972056|+0.500000,-0.128643,+0.000000"},
   {  1,"+0.361408,+0.368691,+0.000000|+0.361408,+0.368691,+1.972056|+0.497334,+0.138592,+1.972056|+0.497334,+0.138592,+0.000000"},
   {  1,"+0.128643,+0.500000,+0.000000|+0.128643,+0.500000,+1.972056|+0.361408,+0.368691,+1.972056|+0.361408,+0.368691,+0.000000"},
   {  1,"-0.138592,+0.497334,+0.000000|-0.138592,+0.497334,+1.972056|+0.128643,+0.500000,+1.972056|+0.128643,+0.500000,+0.000000"},
   {  1,"-0.368691,+0.361408,+0.000000|-0.368691,+0.361408,+1.972056|-0.138592,+0.497334,+1.972056|-0.138592,+0.497334,+0.000000"},
   {  1,"-0.500000,+0.128643,+0.000000|-0.500000,+0.128643,+1.972056|-0.368691,+0.361408,+1.972056|-0.368691,+0.361408,+0.000000"},
   {  1,"-0.497334,-0.138592,+0.000000|-0.497334,-0.138592,+1.972056|-0.500000,+0.128643,+1.972056|-0.500000,+0.128643,+0.000000"},
   {  1,"-0.361408,-0.368691,+0.000000|-0.361408,-0.368691,+1.972056|-0.497334,-0.138592,+1.972056|-0.497334,-0.138592,+0.000000"},
   {  1,"-0.128643,-0.500000,+0.000000|-0.128643,-0.500000,+1.972056|-0.361408,-0.368691,+1.972056|-0.361408,-0.368691,+0.000000"},
   {  1,"+0.138592,-0.497334,+0.000000|+0.138592,-0.497334,+1.972056|-0.128643,-0.500000,+1.972056|-0.128643,-0.500000,+0.000000"},
   {  0,"-0.128643,-0.500000,+0.000000|-0.361408,-0.368691,+0.000000|-0.497334,-0.138592,+0.000000|-0.500000,+0.128643,+0.000000|-0.368691,+0.361408,+0.000000|-0.138592,+0.497334,+0.000000|+0.128643,+0.500000,+0.000000|+0.361408,+0.368691,+0.000000|+0.497334,+0.138592,+0.000000|+0.500000,-0.128643,+0.000000|+0.368691,-0.361408,+0.000000|+0.138592,-0.497334,+0.000000"}
};
static objectdef Cylinder = {
   "Cylinder",
	{ 0.0,0.0,0.0 },
    2, { "255,255,0|215,43,0" },
   14, CylinderPolygons
};

