//
//  NeuralNetWorkOp.hpp
//  MNN
//
//  Created by MNN on 2019/06/27.
//  Copyright © 2018, Alibaba Group Holding Limited
//

namespace MNN {
namespace Express {
enum PaddingMode {CAFFE, VALID, SAME};
enum PoolingMode {MAXPOOL, AVEPOOL};
enum PadValueMode {CONSTANT, REFLECT, SYMMETRIC};
MNN_PUBLIC VARP _Input(INTS dims = {}, Dimensionformat format = NC4HW4, halide_type_t type = halide_type_of<float>());
MNN_PUBLIC VARP _Clone(VARP source, bool deepCopy=false);

MNN_PUBLIC VARP _Scalar(const void* ptr, halide_type_t type);

template <typename T>
VARP _Scalar(T value) {
    return _Scalar(&value, halide_type_of<T>());
}


MNN_PUBLIC VARP _Const(float value, INTS dims = {}, Dimensionformat format = NHWC);
MNN_PUBLIC VARP _Const(const void* ptr, INTS dims = {}, Dimensionformat format = NHWC,
                       halide_type_t type = halide_type_of<float>());
MNN_PUBLIC VARP _TrainableParam(float value, INTS dims, Dimensionformat format);
MNN_PUBLIC VARP _TrainableParam(const void* ptr, INTS dims, Dimensionformat format,
                                  halide_type_t type = halide_type_of<float>());
MNN_PUBLIC VARP _Conv(VARP weight, VARP bias, VARP x, PaddingMode pad = VALID, INTS stride = {1, 1},
                      INTS dilate = {1, 1}, int group = 1, INTS pads = {0, 0});

MNN_PUBLIC VARP _Conv(float weight, float bias, VARP x, INTS channel, INTS kernelSize, PaddingMode pad = VALID,
                      INTS stride = {1, 1}, INTS dilate = {1, 1}, int group = 1);
MNN_PUBLIC VARP _Conv(std::vector<float>&& weight, std::vector<float>&& bias, VARP x, INTS channel, INTS kernelSize,
                      PaddingMode pad = VALID, INTS stride = {1, 1}, INTS dilate = {1, 1}, int group = 1, INTS pads = {0, 0});
MNN_PUBLIC VARP _Deconv(VARP weight, VARP bias, VARP x, PaddingMode pad = VALID, INTS stride = {1, 1},
                                INTS dilate = {1, 1}, int group = 1, INTS pads = {0, 0});
MNN_PUBLIC VARP _MaxPool(VARP x, INTS kernel, INTS stride, PaddingMode pad = VALID, INTS pads= {0, 0});
MNN_PUBLIC VARP _AvePool(VARP x, INTS kernel, INTS stride, PaddingMode pad = VALID, INTS pads= {0, 0});
MNN_PUBLIC VARP _Reshape(VARP x, INTS dim, Dimensionformat format = NHWC);
MNN_PUBLIC VARP _Reshape(VARP x, VARP shape);
MNN_PUBLIC VARP _Scale(VARP x, int channels, std::vector<float>&& scales, std::vector<float>&& bias);

MNN_PUBLIC VARP _Relu(VARP x, float slope = 0.0f);
MNN_PUBLIC VARP _Relu6(VARP x);
MNN_PUBLIC VARP _PRelu(VARP x, std::vector<float> &&slopes);
MNN_PUBLIC VARP _Softmax(VARP x, int axis);
MNN_PUBLIC VARP _Softplus(VARP x);
MNN_PUBLIC VARP _Softsign(VARP x);
MNN_PUBLIC std::vector<VARP> _Split(VARP x, INTS points, int axis);
MNN_PUBLIC VARP _Slice(VARP x, VARP starts, VARP sizes);
MNN_PUBLIC VARP _StridedSlice(VARP x, VARP begin, VARP end, VARP strided, halide_type_t type,
                                      int32_t beginMask, int32_t endMask, int32_t ellipsisMask,
                                      int32_t newAxisMask, int32_t shrinkAxisMask);
MNN_PUBLIC VARP _Concat(VARPS xs, int axis);
MNN_PUBLIC VARP _Convert(VARP x, Dimensionformat dest);
MNN_PUBLIC VARP _Transpose(VARP x, INTS perm);
MNN_PUBLIC VARP _Transpose(VARP x, VARP perm);
MNN_PUBLIC VARP _ChannelShuffle(VARP x, int group);
MNN_PUBLIC VARP _ChangeInputFormat(VARP x, Dimensionformat requireInput);
MNN_PUBLIC VARP _Conv2DBackPropFilter(VARP weight, VARP input, VARP inputGrad, PaddingMode pad = VALID, INTS stride = {1, 1}, INTS dilate = {1, 1}, int group = 1, INTS pads = {0, 0});
MNN_PUBLIC VARP _PoolGrad(VARP originInput, VARP originOutput, VARP inputGrad, INTS kernel, INTS stride, PoolingMode type, PaddingMode pad = VALID, INTS pads= {0, 0});
// FIXME: move the api to Array Ops
MNN_PUBLIC VARP _ReverseSequence(VARP x, VARP y, int batchDim, int seqDim);
// FIXME: move the api to Image Ops
MNN_PUBLIC VARP _Crop(VARP x, VARP s, int axis, INTS offset);
MNN_PUBLIC VARP _Resize(VARP x, float xScale, float yScale);
MNN_PUBLIC VARP _Pad(VARP x, VARP pads, PadValueMode mode = CONSTANT);
MNN_PUBLIC VARP _ExpandDims(VARP x, int axis);
MNN_PUBLIC VARP _ExpandDims(VARP x, VARP axis);

MNN_PUBLIC VARP _Shape(VARP x);
MNN_PUBLIC VARP _Stack(VARPS values, int axis=0);
enum InterpolationMethod {BILINEAR, NEAREST};
MNN_PUBLIC VARP _CropAndResize(VARP image, VARP boxes, VARP indexes, VARP sizes, float extrapolation, InterpolationMethod method);
MNN_PUBLIC VARP _Fill(VARP s, VARP v);
MNN_PUBLIC VARP _Tile(VARP x, VARP mul);
MNN_PUBLIC VARP _Gather(VARP embedding, VARP indices);
MNN_PUBLIC VARP _GatherV2(VARP params, VARP indices, VARP axis = nullptr);
MNN_PUBLIC VARP _Squeeze(VARP x, INTS axes = {});
MNN_PUBLIC VARP _Unsqueeze(VARP x, INTS axes = {});
MNN_PUBLIC VARP _BatchToSpaceND(VARP input, VARP block_shape, VARP crops);
MNN_PUBLIC VARP _GatherND(VARP params, VARP indices);
MNN_PUBLIC VARP _Selu(VARP features, float scale, float alpha);
MNN_PUBLIC VARP _Size(VARP input);
MNN_PUBLIC VARP _Elu(VARP features, float alpha=1.0);
MNN_PUBLIC VARP _MatrixBandPart(VARP input, VARP num_lower, VARP num_upper);
MNN_PUBLIC std::vector<VARP> _Moments(VARP x, INTS axis, VARP shift, bool keepDims);
MNN_PUBLIC VARP _SetDiff1D(VARP x, VARP y); 
MNN_PUBLIC VARP _SpaceToDepth(VARP input, int block_size);
MNN_PUBLIC VARP _SpaceToBatchND(VARP input, VARP block_shape, VARP paddings);
MNN_PUBLIC VARP _ZerosLike(VARP input);
MNN_PUBLIC std::vector<VARP> _Unstack(VARP value, int axis=0);
MNN_PUBLIC VARP _Rank(VARP input);
MNN_PUBLIC VARP _Range(VARP start, VARP limit, VARP delta);
MNN_PUBLIC VARP _Interp(VARPS xs, float widthScale, float heightScale, int outputWidth, int outputHeight, int resizeType, bool alignCorners);
} // namespace Express
} // namespace MNN
