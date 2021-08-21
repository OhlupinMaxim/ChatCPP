#pragma once

#include <iostream>
#include <memory>

const static std::string staticFilesPath = "../../static";
const static std::string staticFilesRoot = "../api/static";
const static std::string staticPathExceptionMessage = "Template's Folder not Found (../../static is not exists)";
const static std::string staticRootExceptionMessage = "Create Static's Folder Error! (../api/static is not exists)";

const static std::string apiRootPath = "../api";

// _____________TEMPLATES__________________
const static std::string templates = staticFilesRoot + "/templates";
const static std::string homePage = templates + "/index.html";
const static std::string roomPage = templates + "/room.html";

// ______________ERR_TEMPLATES_____________
const static std::string errTemplates = templates + "/errPages";
const static std::string err404page = errTemplates + "/404.html";
const static std::string err400page = errTemplates + "/400.html";
const static std::string err500page = errTemplates + "/500.html";


