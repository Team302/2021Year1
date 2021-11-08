
//====================================================================================================================================================
// Copyright 2020 Lake Orion Robotics FIRST Team 302
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#include <ctre/phoenix/Sensors/PigeonIMU.h>
#include <hw/DragonPigeon.h>
#include <memory>

using namespace std;

using namespace ctre::phoenix::sensors;

DragonPigeon::DragonPigeon
(
    int    canID
) : m_pigeon(make_unique<PigeonIMU>(canID))
{
    m_pigeon = make_unique<PigeonIMU>( canID );
    m_pigeon.get()->ConfigFactoryDefault();

    m_pigeon.get()->SetStatusFramePeriod( PigeonIMU_StatusFrame::PigeonIMU_BiasedStatus_4_Mag, 120, 0);
    m_pigeon.get()->SetStatusFramePeriod( PigeonIMU_StatusFrame::PigeonIMU_CondStatus_11_GyroAccum, 120, 0);
    m_pigeon.get()->SetStatusFramePeriod( PigeonIMU_StatusFrame::PigeonIMU_BiasedStatus_6_Accel, 120, 0); // using fused heading not yaw
//    m_pigeon.get()->SetStatusFramePeriod( PigeonIMU_StatusFrame::PigeonIMU_CondStatus_9_SixDeg_YPR, 120, 0); // using fused heading not yaw
}


double DragonPigeon::GetPitch()
{
    return -(GetRawPitch()); //TODO: add inversions into code
}

double DragonPigeon::GetRoll()
{
    return GetRawRoll();
}

double DragonPigeon::GetYaw()
{
    return GetRawYaw();  // reset should have taken care of this
}

void DragonPigeon::ReZeroPigeon( double angleDeg, int timeoutMs)
{
    m_pigeon.get()->SetFusedHeading( angleDeg, timeoutMs);
}

double DragonPigeon::GetRawPitch()
{
    double ypr[3]; // yaw = 0 pitch = 1 roll = 2
    m_pigeon.get()->GetYawPitchRoll(ypr);
    return ypr[1];}

double DragonPigeon::GetRawRoll()
{
    double ypr[3]; // yaw = 0 pitch = 1 roll = 2
    m_pigeon.get()->GetYawPitchRoll(ypr);
    return ypr[2];
}

double DragonPigeon::GetRawYaw()
{
    //double yaw = m_pigeon.get()->GetFusedHeading();
    double ypr[3]; // yaw = 0 pitch = 1 roll = 2
    m_pigeon.get()->GetYawPitchRoll(ypr);
    double yaw = ypr[0];
    // normalize it to be between -180 and + 180
    if ( yaw > 180 )
    {
        yaw -= 360.0;
    }
    else if ( yaw < -180 )
    {
        yaw += 360.0;
    }
    return yaw;  
}