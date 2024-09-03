/******************************************************************************
 * Copyright (C) [2024] [github.com/babuge]
 *
 * [BBGProject] is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 *
 *
 * 文件名称 ：   ResouceLoadCommon.h
 * 文件标识 ：
 * 摘 要 ：     由于资源加载的抽象基类
 * 当前版本 ：   v0.01.0
 * 作 者 ：     babuge
 * 完成日期 ：
 * 取代版本 ：   v0.0.0
 * 原作者   ：  babuge
 * 完成日期 ：  2024/08/14
 ******************************************************************************/

#pragma once

#include "CommonBase.h"
#include <QString>

namespace ResourceSpace
{

typedef enum class ResourceType_ : int
{
    UNKNOW = 0,
    MODULE,
    PLUGIN,
    ICON,
    COMPONENY,
    BINARYFILE,
    ERROR
} ResourceType;

}  // namespace ResourceSpace

using ResourceSpace::ResourceType;
class IResouceLoad
{
public:
    virtual bool loadResource(const QString &fileName, const ResourceType &type)   = 0;
    virtual PtrType GetResource(const QString &fileName, const ResourceType &type) = 0;
    virtual void freeResource(const QString &moduleName, const ResourceType &type) = 0;
};
