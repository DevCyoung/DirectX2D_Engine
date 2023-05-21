#include "Time.h"
#include "Application.h"


extern engine::Application application;

namespace engine
{
    double Time::mDeltaTime = 0.0l;
    double Time::mSecond = 0.0l;

    LARGE_INTEGER Time::mCpuFrequency = {};
    LARGE_INTEGER Time::mPrevFrequency = {};
    LARGE_INTEGER Time::mCurFrequency = {};

    Time::Time()
    {
    }

    Time::~Time()
    {
    }

    void Time::Initiailize()
    {
        // CPU ���� ������ ��������
        QueryPerformanceFrequency(&mCpuFrequency);

        // ���α׷��� ó�� �����Ҷ� ������
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::Update()
    {
        //����
        QueryPerformanceCounter(&mCurFrequency);

        const double differnceFrequency = static_cast<double>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

        mDeltaTime = differnceFrequency / static_cast<double>(mCpuFrequency.QuadPart);

        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::Render(const HDC hdc)
    {
        mSecond += mDeltaTime;

        if (mSecond > 1.0l)
        {
            const HWND hWnd = application.GetHwnd();            

            wchar_t buffer[256] = {};
            const double fps = 1.0l / mDeltaTime;

            swprintf_s(buffer, 256, L"FPS : %lf", fps);
            SetWindowText(hWnd, buffer);

            mSecond = 0.0l;                                    
        }
    }
}