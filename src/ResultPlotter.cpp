//
// Created by paulina on 15.02.17.
//

#include <cstdlib>
#include <aquila/source/PlainTextFile.h>
#include <aquila/source/WaveFile.h>
#include "../inc/ResultPlotter.h"

ResultPlotter::ResultPlotter() {

}

ResultPlotter::~ResultPlotter() {

}

void ResultPlotter::plot(Aquila::WaveFile wav) {
    system("touch sigToPlot");
    Aquila::PlainTextFile::save(wav, "sigToPlot");
    system("gnuplot gnuscript.pg");

}
