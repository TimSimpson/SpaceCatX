import("Macaroni", "ProjectTemplates", "1")
require "SimpleProject"

SimpleBoostProject{
  group="SpaceCatX",
  project="Cat",
  version="DEV",
  libShortName="Cat",
  src="src",
  target="target",
  dependencies = {
    loadBoostLib("date_time"),
    loadBoostLib("headers"),
    load("Lp3", "Lp3.Engine.Core", "DEV"):Target("lib"),
    load("Lp3", "Lp3.Engine.Gfx", "DEV"):Target("lib")
  },
  -- exes={
  --   "CatX.cpp",
  -- },
  -- tests={
  --    "Macaroni/Tests/Blocks/BlocksTest.cpp",
  --    "Macaroni/Tests/Const/ConstTest.cpp",
  --    "Macaroni/Tests/Initializers/ConstructorInitializersTest.cpp",
  --    "Macaroni/Tests/Initializers/FieldInitializersTest.cpp",
  --    "Macaroni/Tests/Typedefs/TypedefsTest.cpp",
  -- },
};
