#pragma once
#include <cstdint>

    enum InferModelComb
    {

    };

    enum ConnectType
    {

    };

    struct ModuleOutPutInf
    {
    };

    struct ModuleInitArgs
    {
    };

    struct ModulrConnectDesc
    {
        /* data */
    };

    struct ModulesInfo
    {
        /* data */
    };

    enum InferEngine
    {
        MindX = 0,
        Lite = 1,
    };
    enum ShapeType
    {
        STATIC_SHAPE = 0,
        DYNAMIC_SHAPE = 1,
        DYNAMIC_BATCHSIZE = 2,
        DYNAMIC_IMAGESIZE = 3
    };
    struct ShapeInfo
    {
        ShapeType shapeType;
        uint32_t batchSize;
        uint8_t channel;
        uint32_t height;
        uint32_t width;
    };

