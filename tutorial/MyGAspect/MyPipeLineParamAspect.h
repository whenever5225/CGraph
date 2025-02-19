/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: MyPipeLineParamAspect.h
@Time: 2021/10/5 11:48 上午
@Desc: 
***************************/

#ifndef CGRAPH_MYPIPELINEPARAMASPECT_H
#define CGRAPH_MYPIPELINEPARAMASPECT_H

#include "../../src/CGraph.h"
#include "../MyGParam/MyParam.h"

class MyPipeLineParamAspect : public CGraph::GAspect {
public:
    CSTATUS beginRun() override {
        CSTATUS status = STATUS_OK;

        /**
         * 在切面层，获取pipeline中的参数值信息，进行一些逻辑处理
         * 可以用于异常判断、限流等逻辑
         * */
        auto* pipelineParam = this->getPipelineParam<MyParam>("param1");
        if (nullptr == pipelineParam) {
            return STATUS_RES;
        }

        /** 遇到并发情况，请考虑加锁保护（参考 T05-Param 中逻辑） */
        int cnt = pipelineParam->iCount;
        CGraph::CGRAPH_ECHO("----> [MyPipeLineParamAspect] pipeline param iCount is [%d] before run.", cnt);

        if (cnt < 0) {
            /** 模拟：在切面中，对pipeline中的参数，做一些异常值的处理逻辑
             * 在 beginRun() 切面中 返回非STATUS_OK值，则pipeline停止执行
             * */
            status = STATUS_ERR;
        }

        return status;
    }
};

#endif //CGRAPH_MYPIPELINEPARAMASPECT_H
