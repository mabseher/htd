/*
 * File:   main.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2016, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 *
 * This file is part of htd.
 *
 * htd is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * htd is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <htd/main.hpp>
#include <htd_cli/main.hpp>

htd_cli::OptionManager * createOptionManager(void)
{
    htd_cli::OptionManager * manager = new htd_cli::OptionManager();

    htd_cli::Option * helpOption = new htd_cli::Option("help", "Print usage information and exit.", 'h');

    manager->registerOption(helpOption);

    htd_cli::SingleValueOption * seedOption = new htd_cli::SingleValueOption("seed", "Set the seed for the random number generator to <seed>", "seed", 's');

    manager->registerOption(seedOption);

    htd_cli::Choice * inputFormatChoice = new htd_cli::Choice("input", "Assume that the input graph is given in format <format>.\n  (See https://github.com/mabseher/htd/formats.md for information about the available input formats.)", "format");

    inputFormatChoice->addPossibility("gr", "Use the input format 'gr'.");
    //inputFormatChoice->addPossibility("hg", "Use the input format 'hg'.");
    //inputFormatChoice->addPossibility("lp", "Use the input format 'lp'.");
    inputFormatChoice->addPossibility("mgr", "Use the input format 'mgr'.");

    inputFormatChoice->setDefaultValue("gr");

    manager->registerOption(inputFormatChoice, "Input-Specific Options");

    htd_cli::Choice * outputFormatChoice = new htd_cli::Choice("output", "Set the output format of the decomposition to <format>.\n  (See https://github.com/mabseher/htd/formats.md for information about the available output formats.)", "format");

    outputFormatChoice->addPossibility("td", "Use the output format 'td'.");
    //outputFormatChoice->addPossibility("graphml", "Use the output format 'graphml'.");
    outputFormatChoice->addPossibility("human", "Provide a human-readable output of the decomposition.");
    outputFormatChoice->addPossibility("width", "Provide only the maximum bag size of the decomposition.");

    outputFormatChoice->setDefaultValue("td");

    manager->registerOption(outputFormatChoice, "Output-Specific Options");

    htd_cli::Choice * orderingAlgorithmChoice = new htd_cli::Choice("ordering", "Set the ordering algorithm which shall be used to <algorithm>.", "algorithm");

    orderingAlgorithmChoice->addPossibility("min-fill", "Minimum-fill ordering algorithm");
    orderingAlgorithmChoice->addPossibility("min-degree", "Minimum-degree ordering algorithm");
    orderingAlgorithmChoice->addPossibility("max-cardinality", "Maximum cardinality search ordering algorithm");

    orderingAlgorithmChoice->setDefaultValue("min-fill");

    manager->registerOption(orderingAlgorithmChoice, "Algorithm Options");

    return manager;
}

bool handleOptions(int argc, const char * const * const argv, htd_cli::OptionManager & optionManager)
{
    bool ret = true;

    try
    {
        optionManager.parse(argc, argv);
    }
    catch (const std::runtime_error & exception)
    {
        std::cout << "INVALID PROGRAM CALL: " << exception.what() << std::endl;

        ret = false;
    }

    const htd_cli::Option & helpOption = optionManager.accessOption("help");

    const htd_cli::Choice & orderingAlgorithmChoice = optionManager.accessChoice("ordering");

    const htd_cli::SingleValueOption & seedOption = optionManager.accessSingleValueOption("seed");

    if (ret && helpOption.used())
    {
        std::cout << "USAGE: " << argv[0] << " [options...] < input" << std::endl << std::endl;

        optionManager.printHelp(std::cout);

        ret = false;
    }

    if (ret)
    {
        if (seedOption.used())
        {
            std::size_t index = 0;

            const std::string & value = seedOption.value();

            if (value.empty() || value.find_first_not_of("01234567890") != std::string::npos)
            {
                std::cerr << "INVALID SEED: " << seedOption.value() << std::endl;

                ret = false;
            }

            if (ret)
            {
                unsigned long seed = std::stoul(seedOption.value(), &index, 10);

                if (index != seedOption.value().length())
                {
                    std::cerr << "INVALID SEED: " << seedOption.value() << std::endl;

                    ret = false;
                }
                else
                {
                    srand(seed);
                }
            }
        }
        else
        {
            srand(time(NULL));
        }
    }

    if (ret && orderingAlgorithmChoice.used())
    {
        const std::string & value = orderingAlgorithmChoice.value();

        if (value == "min-fill")
        {
            htd::OrderingAlgorithmFactory::instance().setConstructionTemplate(new htd::MinFillOrderingAlgorithm);
        }
        else if (value == "min-degree")
        {
            htd::OrderingAlgorithmFactory::instance().setConstructionTemplate(new htd::MinDegreeOrderingAlgorithm);
        }
        else if (value == "max-cardinality")
        {
            htd::OrderingAlgorithmFactory::instance().setConstructionTemplate(new htd::MaximumCardinalitySearchOrderingAlgorithm());
        }
        else
        {
            std::cerr << "INVALID ORDERING ALGORITHM: " << orderingAlgorithmChoice.value() << std::endl;

            ret = false;
        }
    }

    return ret;
}

void decomposeGr(const htd::ITreeDecompositionExporter & exporter)
{
    htd::GrFormatImporter importer;

    htd::IMultiGraph * graph = importer.import(std::cin);

    if (graph != nullptr)
    {
        htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

        htd::ITreeDecomposition * decomposition = algorithm->computeDecomposition(*graph);

        delete algorithm;

        if (decomposition != nullptr)
        {
            exporter.write(*decomposition, *graph, std::cout);

            delete decomposition;
        }
        else
        {
            std::cerr << "NO TREE DECOMPOSITION COMPUTED!" << std::endl;
        }

        delete graph;
    }
    else
    {
        std::cerr << "NO VALID INSTANCE PROVIDED!" << std::endl;
    }
}

void decomposeLp(const htd::ITreeDecompositionExporter & exporter)
{
    htd::LpFormatImporter importer;

    htd::NamedMultiHypergraph<std::string, std::string> * graph = importer.import(std::cin);

    if (graph != nullptr)
    {
        htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

        htd::ITreeDecomposition * decomposition = algorithm->computeDecomposition(graph->internalGraph());

        delete algorithm;

        if (decomposition != nullptr)
        {
            exporter.write(*decomposition, *graph, std::cout);

            delete decomposition;
        }
        else
        {
            std::cerr << "NO TREE DECOMPOSITION COMPUTED!" << std::endl;
        }

        delete graph;
    }
    else
    {
        std::cerr << "NO VALID INSTANCE PROVIDED!" << std::endl;
    }
}

void decomposeMGr(const htd::ITreeDecompositionExporter & exporter)
{
    htd::MGrFormatImporter importer;

    htd::IMultiHypergraph * graph = importer.import(std::cin);

    if (graph != nullptr)
    {
        htd::ITreeDecompositionAlgorithm * algorithm = htd::TreeDecompositionAlgorithmFactory::instance().getTreeDecompositionAlgorithm();

        htd::ITreeDecomposition * decomposition = algorithm->computeDecomposition(*graph);

        delete algorithm;

        if (decomposition != nullptr)
        {
            exporter.write(*decomposition, *graph, std::cout);

            delete decomposition;
        }
        else
        {
            std::cerr << "NO TREE DECOMPOSITION COMPUTED!" << std::endl;
        }

        delete graph;
    }
    else
    {
        std::cerr << "NO VALID INSTANCE PROVIDED!" << std::endl;
    }
}

int main(int argc, const char * const * const argv)
{
    int ret = 0;

    htd_cli::OptionManager * optionManager = createOptionManager();

    if (handleOptions(argc, argv, *optionManager))
    {
        const htd_cli::Choice & inputFormatChoice = optionManager->accessChoice("input");

        const htd_cli::Choice & outputFormatChoice = optionManager->accessChoice("output");

        const std::string & outputFormat = outputFormatChoice.value();

        htd::ITreeDecompositionExporter * exporter = nullptr;

        if (outputFormat == "td")
        {
            exporter = new htd::TdFormatExporter();
        }
        else if (outputFormat == "human")
        {
            exporter = new htd::HumanReadableExporter();
        }
        else if (outputFormat == "width")
        {
            exporter = new htd::WidthExporter();
        }
        else
        {
            std::cerr << "INVALID OUTPUT FORMAT: " << outputFormat << std::endl;

            ret = 1;
        }

        if (ret == 0)
        {
            const std::string & inputFormat = inputFormatChoice.value();

            if (inputFormat == "gr")
            {
                decomposeGr(*exporter);
            }
            else if (inputFormat == "lp")
            {
                decomposeLp(*exporter);
            }
            else if (inputFormat == "mgr")
            {
                decomposeMGr(*exporter);
            }
            else
            {
                std::cerr << "INVALID INPUT FORMAT: " << inputFormat << std::endl;

                ret = 1;
            }
        }
    }

    delete optionManager;

    return ret;
}
