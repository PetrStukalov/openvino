// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>
#include "shared_test_classes/single_layer/activation.hpp"
#include "common_test_utils/test_constants.hpp"

using namespace LayerTestsDefinitions;
using namespace ngraph::helpers;
namespace {
TEST_P(ActivationLayerTest, Serialize) {
    Serialize();
}
// Common params
const std::vector<InferenceEngine::Precision> inputPrecisions = {
        InferenceEngine::Precision::FP32
        // TODO: Fix Issue-27390
        // InferenceEngine::Precision::I16,
        // InferenceEngine::Precision::U8
};

const std::vector<InferenceEngine::Precision> netPrecisions = {
        InferenceEngine::Precision::FP32,
        InferenceEngine::Precision::FP16
};

const std::map<ActivationTypes, std::vector<std::vector<float>>> activationTypes = {
        {Sigmoid,               {}},
        {Tanh,                  {}},
        {Relu,                  {}},
        {Exp,                   {}},
        {Log,                   {}},
        {Sign,                  {}},
        {Abs,                   {}},
        {Clamp,                 {{-2.0f, 2.0f}}},
        {Negative,              {}},
        {Acos,                  {}},
        {Acosh,                 {}},
        {Asin,                  {}},
        {Asinh,                  {}},
        {Atan,                  {}},
        {Cos,                   {}},
        {Cosh,                  {}},
        {Floor,                 {}},
        {Sin,                   {}},
        {Sinh,                  {}},
        {Sqrt,                  {}},
        {Tan,                   {}},
        {Elu,                   {{0.1f}}},
        {Erf,                   {}},
        {HardSigmoid,           {{0.2f, 0.5f}}},
        {Selu,                  {{1.6732f, 1.0507f}}},
        {Ceiling,               {}},
        {Mish,                  {}},
        {HSwish,                {}},
        {Swish,                 {{0.3f}}},
        {SoftPlus,              {}},
        {HSigmoid,              {}},
        {RoundHalfToEven,       {}},
        {RoundHalfAwayFromZero, {}},
        {Erf,                   {}},
        {GeluErf,               {}},
        {GeluTanh,              {}}
};

const std::map<ActivationTypes, std::vector<std::vector<float>>> activationParamTypes = {
    {PReLu, {{-0.01f}}},
    {LeakyRelu, {{0.01f}}}
};

std::map<std::vector<size_t>, std::vector<std::vector<size_t>>> basic = {
        {{1, 50}, {{}}},
        {{1, 128}, {{}}},
};

std::map<std::vector<size_t>, std::vector<std::vector<size_t>>> preluBasic = {
        {{1, 50}, {{1}, {50}}},
        {{1, 128}, {{1}, {128}}},
};

const auto basicCases = ::testing::Combine(
        ::testing::ValuesIn(CommonTestUtils::combineParams(activationTypes)),
        ::testing::ValuesIn(netPrecisions),
        ::testing::Values(InferenceEngine::Precision::UNSPECIFIED),
        ::testing::Values(InferenceEngine::Precision::UNSPECIFIED),
        ::testing::Values(InferenceEngine::Layout::ANY),
        ::testing::Values(InferenceEngine::Layout::ANY),
        ::testing::ValuesIn(CommonTestUtils::combineParams(basic)),
        ::testing::Values(CommonTestUtils::DEVICE_CPU)
);

const auto basicPreluCases = ::testing::Combine(
        ::testing::ValuesIn(CommonTestUtils::combineParams(activationParamTypes)),
        ::testing::ValuesIn(netPrecisions),
        ::testing::Values(InferenceEngine::Precision::UNSPECIFIED),
        ::testing::Values(InferenceEngine::Precision::UNSPECIFIED),
        ::testing::Values(InferenceEngine::Layout::ANY),
        ::testing::Values(InferenceEngine::Layout::ANY),
        ::testing::ValuesIn(CommonTestUtils::combineParams(preluBasic)),
        ::testing::Values(CommonTestUtils::DEVICE_CPU)
);


INSTANTIATE_TEST_SUITE_P(smoke_Activation_Basic, ActivationLayerTest, basicCases, ActivationLayerTest::getTestCaseName);
INSTANTIATE_TEST_SUITE_P(smoke_Activation_Basic_Prelu, ActivationLayerTest, basicPreluCases, ActivationLayerTest::getTestCaseName);

INSTANTIATE_TEST_SUITE_P(smoke_Activation_Basic, ActivationParamLayerTest, basicPreluCases, ActivationLayerTest::getTestCaseName);

INSTANTIATE_TEST_SUITE_P(smoke_Activation_Basic, ActivationDynamicLayerTest, basicCases, ActivationLayerTest::getTestCaseName);

}  // namespace
