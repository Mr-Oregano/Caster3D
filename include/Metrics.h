#pragma once

#include <cstddef>

struct Metrics
{
	double avg_hit_tests_per_raycast;
	double avg_raycasts_per_pixel;
	std::size_t raycast_count;
	std::size_t samples_per_pixel;
	std::size_t pixel_count;
	std::size_t triangle_count;
	std::size_t bvh_size;
};

extern Metrics metrics;