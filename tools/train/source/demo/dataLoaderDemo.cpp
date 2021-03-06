//
//  dataLoaderDemo.cpp
//  MNN
//
//  Created by MNN on 2019/11/20.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#include <iostream>
#include "DataLoader.hpp"
#include "DataLoaderConfig.hpp"
#include "DemoUnit.hpp"
#include "LambdaTransform.hpp"
#include "MNN_generated.h"
#include "MnistDataset.hpp"
#include "RandomSampler.hpp"
#include "StackTransform.hpp"
#include "TransformDataset.hpp"

#ifdef MNN_USE_OPENCV
#include <opencv2/opencv.hpp> // use opencv to show pictures
using namespace cv;
#endif

using namespace std;

/*
 * this is an demo for how to use the DataLoader
 */

class DataLoaderDemo : public DemoUnit {
public:
    // this function is an example to use the lambda transform
    // here we use lambda transform to normalize data from 0~255 to 0~1
    static Example func(Example example) {
        // // an easier way to do this
        auto cast       = _Cast(example.data[0], halide_type_of<float>());
        example.data[0] = _Multiply(cast, _Const(1.0f / 255.0f));
        return example;
    }
    virtual int run(int argc, const char* argv[]) override {
        if (argc != 2) {
            cout << "usage: ./runTrainDemo.out DataLoaderDemo /path/to/unzipped/mnist/data/" << endl;
            return 0;
        }

        std::string root = argv[1];

        // train data loader
        const size_t trainDatasetSize = 60000;
        auto trainDataset             = std::make_shared<MnistDataset>(root, MnistDataset::Mode::TRAIN);

        // the lambda transform for one example, we also can do it in batch
        auto trainTransform = std::make_shared<LambdaTransform>(func);

        // // the stack transform, stack [1, 28, 28] to [n, 1, 28, 28]
        // auto trainTransform = std::make_shared<StackTransform>();

        const int trainBatchSize  = 7;
        const int trainNumWorkers = 4;

        auto trainDataLoader =
            DataLoader::makeDataLoader(trainDataset, {trainTransform}, trainBatchSize, true, trainNumWorkers);

        // test data loader
        const size_t testDatasetSize = 10000;
        auto testDataset             = std::make_shared<MnistDataset>(root, MnistDataset::Mode::TEST);

        // the lambda transform for one example, we also can do it in batch
        auto testTransform = std::make_shared<LambdaTransform>(func);

        // // the stack transform, stack [1, 28, 28] to [n, 1, 28, 28]
        // auto testTransform = std::make_shared<StackTransform>();

        const int testBatchSize  = 3;
        const int testNumWorkers = 4;

        auto testDataLoader =
            DataLoader::makeDataLoader(testDataset, {testTransform}, testBatchSize, false, testNumWorkers);

        const size_t iterations = testDatasetSize / testBatchSize;

        for (int i = 0; i < iterations; i++) {
            auto trainData = trainDataLoader->next();
            auto testData  = testDataLoader->next();

            auto data  = trainData[0].data[0]->readMap<float>();
            auto label = trainData[0].target[0]->readMap<uint8_t>();

            cout << "index: " << i << " train label: " << int(label[0]) << endl;

            // // only show the first picture in the batch
            // imshow("train", Mat(28, 28, CV_32FC1, (void*)data));

            data  = testData[0].data[0]->readMap<float>();
            label = testData[0].target[0]->readMap<uint8_t>();

            cout << "index: " << i << " test label: " << int(label[0]) << endl;

            // // only show the first picture in the batch
            // imshow("test", Mat(28, 28, CV_32FC1, (void*)data));
            // waitKey(-1);
        }
        // this will reset the sampler's internal state, not necessary here
        trainDataLoader->reset();

        // this will reset the sampler's internal state, necessary here, because the test dataset is exhausted
        testDataLoader->reset();
        return 0;
    }
};
DemoUnitSetRegister(DataLoaderDemo, "DataLoaderDemo");
