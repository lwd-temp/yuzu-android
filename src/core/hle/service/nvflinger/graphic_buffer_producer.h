// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2021 yuzu Emulator Project
// Copyright 2010 The Android Open Source Project
// Parts of this implementation were base on:
// https://cs.android.com/android/platform/superproject/+/android-5.1.1_r38:frameworks/native/include/gui/IGraphicBufferProducer.h

#pragma once

#include "common/common_funcs.h"
#include "common/common_types.h"
#include "core/hle/service/nvflinger/ui/fence.h"
#include "core/hle/service/nvflinger/ui/rect.h"
#include "core/hle/service/nvflinger/window.h"

namespace Service::android {

class Parcel;

#pragma pack(push, 1)
struct QueueBufferInput final {
    explicit QueueBufferInput(Parcel& parcel);

    void Deflate(s64* timestamp_, bool* is_auto_timestamp_, Rect* crop_,
                 NativeWindowScalingMode* scaling_mode_, NativeWindowTransform* transform_,
                 u32* sticky_transform_, bool* async_, s32* swap_interval_, Fence* fence_) const {
        *timestamp_ = timestamp;
        *is_auto_timestamp_ = static_cast<bool>(is_auto_timestamp);
        *crop_ = crop;
        *scaling_mode_ = scaling_mode;
        *transform_ = transform;
        *sticky_transform_ = sticky_transform;
        *async_ = static_cast<bool>(async);
        *swap_interval_ = swap_interval;
        *fence_ = fence;
    }

private:
    s64 timestamp{};
    s32 is_auto_timestamp{};
    Rect crop{};
    NativeWindowScalingMode scaling_mode{};
    NativeWindowTransform transform{};
    u32 sticky_transform{};
    s32 async{};
    s32 swap_interval{};
    Fence fence{};
};
#pragma pack(pop)
static_assert(sizeof(QueueBufferInput) == 84, "QueueBufferInput has wrong size");

#pragma pack(push, 1)
struct QueueBufferOutput final {
    QueueBufferOutput();

    void Deflate(u32* width_, u32* height_, u32* transform_hint_, u32* num_pending_buffers_) const {
        *width_ = width;
        *height_ = height;
        *transform_hint_ = transform_hint;
        *num_pending_buffers_ = num_pending_buffers;
    }

    void Inflate(u32 width_, u32 height_, u32 transform_hint_, u32 num_pending_buffers_) {
        width = width_;
        height = height_;
        transform_hint = transform_hint_;
        num_pending_buffers = num_pending_buffers_;
    }

private:
    u32 width{};
    u32 height{};
    u32 transform_hint{};
    u32 num_pending_buffers{};
};
#pragma pack(pop)
static_assert(sizeof(QueueBufferOutput) == 16, "QueueBufferOutput has wrong size");

} // namespace Service::android
