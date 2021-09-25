#pragma once


#include <Poco/File.h>
#include <Poco/Exception.h>

#include "handlers/StaticPath.hpp"

static void createStaticFolder() {
    try {
        std::unique_ptr<Poco::File> file(new Poco::File(staticFilesPath));
        if (!file->isDirectory())
            throw Poco::NotFoundException(staticPathExceptionMessage);
        std::unique_ptr<Poco::File> api_root (new Poco::File(apiRootPath));
        api_root->createDirectory();
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