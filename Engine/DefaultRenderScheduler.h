/* ***** BEGIN LICENSE BLOCK *****
 * This file is part of Natron <http://www.natron.fr/>,
 * Copyright (C) 2016 INRIA and Alexandre Gauthier-Foichat
 *
 * Natron is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Natron is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Natron.  If not, see <http://www.gnu.org/licenses/gpl-2.0.html>
 * ***** END LICENSE BLOCK ***** */

#ifndef NATRON_ENGINE_DEFAULTRENDERSCHEDULER_H
#define NATRON_ENGINE_DEFAULTRENDERSCHEDULER_H
// ***** BEGIN PYTHON BLOCK *****
// from <https://docs.python.org/3/c-api/intro.html#include-files>:
// "Since Python may define some pre-processor definitions which affect the standard headers on some systems, you must include Python.h before any standard headers are included."
#include <Python.h>
// ***** END PYTHON BLOCK *****

#include "Engine/OutputSchedulerThread.h"

NATRON_NAMESPACE_ENTER;


/**
 * @brief A default OutputSchedulerThread implementation for all nodes that perform rendering without updating the viewer
 **/
class DefaultScheduler
: public OutputSchedulerThread
{
    GCC_DIAG_SUGGEST_OVERRIDE_OFF
    Q_OBJECT
    GCC_DIAG_SUGGEST_OVERRIDE_ON

public:

    DefaultScheduler(RenderEngine* engine,
                     const NodePtr& effect);

    virtual ~DefaultScheduler();

    virtual SchedulingPolicyEnum getSchedulingPolicy() const OVERRIDE FINAL;

    virtual void processFrame(const ProcessFrameArgsBase& args) OVERRIDE FINAL;


private:

    virtual void timelineGoTo(TimeValue time) OVERRIDE FINAL;
    virtual void getFrameRangeToRender(TimeValue& first, TimeValue& last) const OVERRIDE FINAL;
    virtual TimeValue timelineGetTime() const OVERRIDE FINAL WARN_UNUSED_RETURN;

    virtual RenderThreadTask* createRunnable(TimeValue frame, bool useRenderStarts, const std::vector<ViewIdx>& viewsToRender) OVERRIDE FINAL WARN_UNUSED_RETURN;

    virtual void handleRenderFailure(ActionRetCodeEnum stat, const std::string& errorMessage) OVERRIDE FINAL;
    virtual void aboutToStartRender() OVERRIDE FINAL;
    virtual void onRenderStopped(bool aborted) OVERRIDE FINAL;

private:

    mutable QMutex _currentTimeMutex;
    TimeValue _currentTime;
};



NATRON_NAMESPACE_EXIT;

#endif // DEFAULTRENDERSCHEDULER_H
