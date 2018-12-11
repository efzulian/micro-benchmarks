//
// Copyright (C) 2017 University of Kaiserslautern
// Microelectronic Systems Design Research Group
//
// Vladimir Rybalkin (rybalkin@eit.uni-kl.de)
// 20. February 2017
//



#ifndef NEURON_H
#define NEURON_H

#include <math.h>       // tanh, log
#include <sys/types.h>

#include "../../common/include/neuron_com.h"






	//====================================================================================================================================================================================================================
	// LSTM
	//====================================================================================================================================================================================================================

	// The dot product corresponding to a single gate of the LSTM memory cell
	 float DotVectorToVector126(float *source, 	// IN  // size: 1.0 + HIGHT_IN_PIX + NUMBER_OF_NEURONS = NUMBER_OF_INPUTS
									  float *weights);	// IN  // size: NUMBER_OF_INPUTS

	// The function of a single LSTM memory cell
	void HiddenLayerSingleMemoryCell(float *source,					// IN  // size: 1.0 + HIGHT_IN_PIX + NUMBER_OF_NEURONS = NUMBER_OF_INPUTS
									 unsigned int currentColumn,	// IN  // The current column of the image
									 float in_state,				// IN  // A single input state
									 float *WGI,   					// IN  // size: NUMBER_OF_INPUTS
									 float *WGF,   					// IN  // size: NUMBER_OF_INPUTS
									 float *WGO,   					// IN  // size: NUMBER_OF_INPUTS
									 float *WCI,   					// IN  // size: NUMBER_OF_INPUTS
									 float WIP,						// IN  // A single peephole weight
									 float WFP,						// IN  // A single peephole weight
									 float WOP,						// IN  // A single peephole weight
									 float *out_state,				// OUT // A single output state
									 float *output);              	// OUT // A single output


	void Hidden_Layer(float *image,					// IN  // size: numberOfColumns * HIGHT_IN_PIX
					  unsigned int numberOfColumns,	// IN  //
					  float *WGI, 					// IN  // size: NUMBER_OF_NEURONS * NUMBER_OF_INPUTS
					  float *WGF, 					// IN  // size: NUMBER_OF_NEURONS * NUMBER_OF_INPUTS
					  float *WGO, 					// IN  // size: NUMBER_OF_NEURONS * NUMBER_OF_INPUTS
					  float *WCI, 					// IN  // size: NUMBER_OF_NEURONS * NUMBER_OF_INPUTS
					  float *WIP, 					// IN  // size: NUMBER_OF_NEURONS
					  float *WFP, 					// IN  // size: NUMBER_OF_NEURONS
					  float *WOP,					// IN  // size: NUMBER_OF_NEURONS
					  float *result);				// OUT // size: numberOfColumns * NUMBER_OF_NEURONS



	//====================================================================================================================================================================================================================
	// Connectionist Temporal Classification Layer (CTC layer)
	//====================================================================================================================================================================================================================

	// The dot product corresponding to a single neuron of the output layer operating on an concatinated output from the forward and the bakward hidden layers
	 float DotVectorToVector201(float *W2,		// IN  // size: NUMBER_OF_NEURONS * 2 + 1
									  float *input_fw, 	// IN  // size: NUMBER_OF_NEURONS
							          float *input_bw);	// IN  // size: NUMBER_OF_NEURONS

	// The function of a single neuron of the output layer
	void OutputLayerSinlgleNeuron(float *W2, 		// IN  // size: NUMBER_OF_NEURONS * 2 + 1
										 float *input_fw,	// IN  // size: NUMBER_OF_NEURONS
										 float *input_bw, 	// IN  // size: NUMBER_OF_NEURONS
										 float *output);	// OUT //

	void Output_Layer(unsigned int numberOfColumns, // IN  //
					  float *W2, 					// IN  // size: NUMBER_OF_CLASSES * (NUMBER_OF_NEURONS * 2 + 1)
					  float *input_fw,			 	// IN  // size: numberOfColumns * NUMBER_OF_NEURONS
					  float *input_bw,			 	// IN  // size: numberOfColumns * NUMBER_OF_NEURONS
					  float *output); 				// OUT // size: numberOfColumns * NUMBER_OF_CLASSE

	// Reconstruct a line from the labels
	void TranslateBack(unsigned int numberOfColumns, float *input, unsigned int *output, unsigned int* str_len, float threshold);

	// The main function for a single image
	void Single_Kernel_BLSTM(
			float *image_fw,
			float *image_bw,
			unsigned int numberOfColumns,
			unsigned int *vecPredictedStringInd,
			unsigned int *str_len);

	//====================================================================================================================================================================================================================
	// AUXILIARY
	//====================================================================================================================================================================================================================


	void print_usage_and_exit(const char *argv0);


#endif
