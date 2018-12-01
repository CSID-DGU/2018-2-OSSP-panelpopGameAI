/*
 * GeneticAlgorithm.cpp
 *
 *  modified on: Dec 1, 2018
 *      Author: blue
 */
#include "GeneticAlgorithm.h"
#include <iostream>
#include <random>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MUATATION_RATE 0.000
// return double real number between 0 to 1
#define RANDOM rand()/(double)(RAND_MAX+1)
#define CROSSOVER_RATE 0.000
#define MAX_GENERATION_SIZE 0
// real value(4) + decimal point(5)
#define CHROMOSOME_LENGTH 9 

// Constructor
GeneticAlgorithm::GeneticAlgorithm() {

	// generate 50 initial parents by random()
	for (int i = 0; i < 50; i++) {

		Weight(random(0, 10), random(0, 10), random(0, 10), random(0, 10));
		list.push_back(Weight);

	}
}

// generate random number between upperLimit and lowLimit
// use random() one-time when generating parents
double GeneticAlgorithm::random(int upperLimit, int lowerLimit) {

	random_device sd;
	mt19937_64 sed(sd());
	uniform_real_distribution<double> range(lowerLimit, upperLimit);

	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
		Weight wg(i + 1, range(sed), range(sed), range(sed), range(sed), range(sed));
		list.push_back(wg);
	}
}

// generate Weight text file for each generation
void GeneticAlgorithm::writeWeightToFile() {

	ofstream fileout("Weights[%d].txt", Generation);

	// write weights to file
	if (fileout.is_open()) {

		for (int i = 0; i < MAX_GENERATION_SIZE; i++) {
			fileout << list.at(i).getAttribute() << endl;
		}

	}
}

// totalFitness : sum of every children in the Generation 
// ptr : pointer of Weight list
int GeneticAlgorithm::selection(int totalFitness, Weight* ptr) {

	// sum of fitnesses to current fitness 
	double sumFitness = 0;

	// generate random point which decides choice
	// 0 < RANDOM < 1
	// why error?
	double piece = (double)(totalFitness * RANDOM);

	// roulette wheel selection
	for (int i = 0; i < MAX_GENERATION_SIZE; i++) {

		for (int j = 0; j < 5; j++) {

			sumFitness += ptr[i].get_verticalBlockWeight();
			sumFitness += ptr[i].get_horizontalBlockWeight();
			sumFitness += ptr[i].get_isMeetGarbageWeight();
			sumFitness += ptr[i].get_isExHighWeight();
			sumFitness += ptr[i].get_isLT2();

		}

		// return selected child's ID
		if (sumFitness < piece) return i;
	}
}

// choose using Roulette wheel and crossOver considering mutation 
// how to crossover 
void GeneticAlgorithm::crossOver(string* chromo1, string * chromo2) {

	int place = 0;
	string g1 = "";
	string g2 = "";

	// crossover randomly
	// 0 < RANDOM < 1
	if (RANDOM < CROSSOVER_RATE) {

		place = (int)(RANDOM * CHROMOSOME_LENGTH);
		g1 = chromo1->substr(0, place) + chromo2->substr(place);
		g2 = chromo2->substr(0, place) + chromo1->substr(place);

	}

	g1 = chromo1;
	g2 = chromo2;
}

// mutate children 
void GeneticAlgorithm::mutation(string * chromo) {

	int num = 0;
	string temp = "";

	// consider mutation on every 5 Weights 
	for (int i = 0; i < 5; i++) {

		// how to mutate
		if (RANDOM < MUATATION_RATE) {
			num = (int)(RANDOM * CHROMOSOME_LENGTH);
			temp = chromo.at(num);

			// if randomly picked string is 1 
			// convert to 0
			if (temp.compare("1") == 0) {
				chromo.replace(num, 1, "0");
			}

			else
				chromo.replace("1");
		}
	}
}

// convert real value weights to binary
// 5 digits from rightmost are decimal point part
// rest of digits are real value
// considering notation of decimal point 
// Assume (0 < weight < 10) => max_chromosome_size = 9
string GeneticAlgorithm::double2bin(double real) {
	// real value part
	int num = (int)real;
	int size = 0;

	// decimal point part
	int point = real - num;

	string temp;
	string binary;

	// real value part 
	// divide with 2
	while (1) {

		// store remainder to temp
		temp += to_string(num % 2);
		num /= 2;

		if (num == 1) { temp += to_string(num); }
		else if (num == 0) break;
	}

	size = temp.size();

	// fill black space with 0
	if (size < 4) {
		temp.replace(0, 4 - size, 0);
	}

	while (1) {
		// reverse stored remainder 
		binary += temp.pop_back();
	}

	// decimal point part
	// size of converted number's decimal point 
	// repeat 5 times
	for (int i = 0; i < 5; i++) {
		point *= 2;

		if (point > 1) {
			tmep += to_string(1);
			point -= 1;
		}
	}

	for (int i = 0; i < 5; i++) {
		binary += temp.pop_back();
	}

	return binary;
}

// convert binary bits to double value weights
// considering notation of decimal point 
double GeneticAlgorithm::bin2double(string * ptr) {

	// size of vector
	int size = ptr->size();
	int num = 0;

	// weight 
	double w = 0;

	// calculating point decimal part
	// repeat 5 times
	for (int i = 5; i > 0; i--) {

		// 0 or 1
		num = ptr->at(size - 1);

		if (num) {

			for (int j = 0; j < i; j++) {
				num *= 2;
			}
			w = 1 % num;
		}
		size--;
	}

	// calculating real value part
	for (int i = size; size >= 0; i--) {

		if (ptr->at(size - 1)) {

		}
	}

	return w;
}

// running GeneticAlgorithm
void GeneticAlgorithm::runGA() {
	
	for (int i = 0; i < 50; i++) {
		list.at[i];
	}

}

// Destructor
GeneticAlgorithm::~GeneticAlgorithm() {  }