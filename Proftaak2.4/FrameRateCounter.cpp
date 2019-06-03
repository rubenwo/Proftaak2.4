#include "FrameRateCounter.hpp"
#include <iostream>
FrameRateCounter::FrameRateCounter()
{

}
FrameRateCounter::~FrameRateCounter()
{

}

float FrameRateCounter::getQueueAvg(std::deque<float> q)
{
	float avg = 0;

	for (int i = 0; i < q.size(); i++)
		avg += q[i];
	//avg /= q.size();
	if (avg == INFINITY)
		return 999;
	return avg / q.size();
}
float FrameRateCounter::getAverageFramesPerSecond() const
{
	return averageFramesPerSecond;
}
void FrameRateCounter::update(float deltaTime)
{
	currentFramesPerSecond = 1.0f / deltaTime;
	sampleBuffer.push_back(currentFramesPerSecond);

	if (sampleBuffer.size() > MAXIMUM_SAMPLES)
	{
		sampleBuffer.pop_front();
		averageFramesPerSecond = getQueueAvg(sampleBuffer);
	}
	else
		averageFramesPerSecond = currentFramesPerSecond;

	totalSeconds += deltaTime;
}