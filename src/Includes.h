#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <stdlib.h>

#define DB_INIT_SIZE 100
#define FEED_SIZE 10
#define EMPTY_STRING ""
#define ADD_IMAGE_STATUS 'i'
#define ADD_VIDEO_STATUS 'v'
#define ADD_TEXT_STATUS 't'

struct Date {
	int day;
	int month;
	int year;
};

using namespace std;