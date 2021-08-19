#pragma once

#include <iostream>
#include <memory>

#include <Poco/File.h>
#include <Poco/Exception.h>

const static std::string staticFilesPath = "../../static";
const static std::string staticFilesRoot = "../api/static";
const static std::string staticPathExceptionMessage = "Template's Folder not Found (../../static is not exists)";
const static std::string staticRootExceptionMessage = "Create Static's Folder Error! (../api/static is not exists)";

const static std::string apiRootPath = "../api";

static void createStaticFolder() {
    try {
        std::unique_ptr<Poco::File> file(new Poco::File(staticFilesPath));
        if (!file->isDirectory())
            throw Poco::NotFoundException(staticPathExceptionMessage);
        file->copyTo(apiRootPath);
        std::unique_ptr<Poco::File> staticFolder(new Poco::File(staticFilesRoot));
        if (!staticFolder->isDirectory())
            throw Poco::FileExistsException(staticRootExceptionMessage);
    } catch (Poco::NotFoundException &ex1) {
        std::cerr << ex1.message() << std::endl;
        throw Poco::ApplicationException();
    } catch (Poco::FileExistsException &ex2) {
        std::cerr << ex2.message() << std::endl;
        throw Poco::ApplicationException();
    }
}