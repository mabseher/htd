/*
 * File:   main.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 *
 * Copyright 2015-2017, Michael Abseher
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
#include <htd_io/main.hpp>
#include <htd_cli/main.hpp>

#include <csignal>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

htd::LibraryInstance * const libraryInstance = htd::createManagementInstance(htd::Id::FIRST);

htd_cli::OptionManager * createOptionManager(void)
{
    htd_cli::OptionManager * manager = new htd_cli::OptionManager();

    try
    {
        htd_cli::Option * helpOption = new htd_cli::Option("help", "Print usage information and exit.", 'h');

        manager->registerOption(helpOption, "General Options");

        htd_cli::Option * versionOption = new htd_cli::Option("version", "Print version information and exit.", 'v');

        manager->registerOption(versionOption, "General Options");

        htd_cli::SingleValueOption * seedOption = new htd_cli::SingleValueOption("seed", "Set the seed for the random number generator to <seed>.", "seed", 's');

        manager->registerOption(seedOption, "General Options");

        htd_cli::Choice * decompositionTypeChoice = new htd_cli::Choice("type", "Compute a graph decomposition of type <type>.", "type");

        decompositionTypeChoice->addPossibility("tree", "Compute a tree decomposition of the input graph.");
        decompositionTypeChoice->addPossibility("hypertree", "Compute a hypertree decomposition of the input graph.");

        decompositionTypeChoice->setDefaultValue("tree");

        manager->registerOption(decompositionTypeChoice, "Decomposition Options");

        htd_cli::Choice * inputFormatChoice = new htd_cli::Choice("input", "Assume that the input graph is given in format <format>.\n  (See https://github.com/mabseher/htd/blob/master/FORMATS.md for information about the available input formats.)", "format");

        inputFormatChoice->addPossibility("gr", "Use the input format 'gr'.");
        inputFormatChoice->addPossibility("lp", "Use the input format 'lp'.");
        inputFormatChoice->addPossibility("hgr", "Use the input format 'hgr'.");

        inputFormatChoice->setDefaultValue("gr");

        manager->registerOption(inputFormatChoice, "Input-Specific Options");

        htd_cli::SingleValueOption * inputFileOption = new htd_cli::SingleValueOption("instance", "Read the input graph from file <instance>.", "instance");

        manager->registerOption(inputFileOption, "Input-Specific Options");

        htd_cli::Choice * outputFormatChoice = new htd_cli::Choice("output", "Set the output format of the decomposition to <format>.\n  (See https://github.com/mabseher/htd/blob/master/FORMATS.md for information about the available output formats.)", "format");

        outputFormatChoice->addPossibility("td", "Use the output format 'td'.");
        outputFormatChoice->addPossibility("human", "Provide a human-readable output of the decomposition.");
        outputFormatChoice->addPossibility("width", "Provide only the maximum bag size of the decomposition.");

        outputFormatChoice->setDefaultValue("td");

        manager->registerOption(outputFormatChoice, "Output-Specific Options");

        htd_cli::Option * printProgressOption = new htd_cli::Option("print-progress", "Print decomposition progress.");

        manager->registerOption(printProgressOption, "Output-Specific Options");

        htd_cli::Choice * strategyChoice = new htd_cli::Choice("strategy", "Set the decomposition strategy which shall be used to <algorithm>.", "algorithm");

        strategyChoice->addPossibility("random", "Use a random vertex ordering.");
        strategyChoice->addPossibility("min-fill", "Minimum fill ordering algorithm");
        strategyChoice->addPossibility("min-degree", "Minimum degree ordering algorithm");
        strategyChoice->addPossibility("min-separator", "Minimum separating vertex set heuristic");
        strategyChoice->addPossibility("max-cardinality", "Maximum cardinality search ordering algorithm");
        strategyChoice->addPossibility("max-cardinality-enhanced", "Enhanced maximum cardinality search ordering algorithm (MCS-M)");
        strategyChoice->addPossibility("challenge", "Use a combination of different decomposition strategies.");

        strategyChoice->setDefaultValue("min-fill");

        manager->registerOption(strategyChoice, "Algorithm Options");

        htd_cli::Choice * preprocessingChoice = new htd_cli::Choice("preprocessing", "Set the preprocessing strategy which shall be used to <strategy>.", "strategy");

        preprocessingChoice->addPossibility("none", "Do not preprocess the input graph.");
        preprocessingChoice->addPossibility("simple", "Use simple preprocessing capabilities.");
        preprocessingChoice->addPossibility("advanced", "Use advanced preprocessing capabilities.");
        preprocessingChoice->addPossibility("full", "Use the full set of preprocessing capabilities.");

        preprocessingChoice->setDefaultValue("none");

        manager->registerOption(preprocessingChoice, "Algorithm Options");

        htd_cli::Option * triangulationMinimizationOption = new htd_cli::Option("triangulation-minimization", "Apply triangulation minimization approach.");

        manager->registerOption(triangulationMinimizationOption, "Algorithm Options");

        htd_cli::Choice * optimizationChoice = new htd_cli::Choice("opt", "Iteratively compute a decomposition which optimizes <criterion>.", "criterion");

        optimizationChoice->addPossibility("none", "Do not perform any optimization.");
        optimizationChoice->addPossibility("width", "Minimize the maximum bag size of the computed decomposition.");

        optimizationChoice->setDefaultValue("none");

        manager->registerOption(optimizationChoice, "Optimization Options");

        htd_cli::SingleValueOption * iterationOption = new htd_cli::SingleValueOption("iterations", "Set the number of iterations to be performed during optimization to <count> (0 = infinite). (Default: 10)", "count");

        manager->registerOption(iterationOption, "Optimization Options");

        htd_cli::SingleValueOption * patienceOption = new htd_cli::SingleValueOption("patience", "Terminate the algorithm if more than <amount> iterations did not lead to an improvement (-1 = infinite). (Default: -1)", "amount");

        manager->registerOption(patienceOption, "Optimization Options");
    }
    catch (const std::runtime_error & exception)
    {
        std::cout << "SETUP FOR OPTION-MANAGER FAILED: " << exception.what() << std::endl;

        delete manager;

        manager = nullptr;
    }

    return manager;
}

bool handleOptions(int argc, const char * const * const argv, htd_cli::OptionManager & optionManager, htd::LibraryInstance * const manager)
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

    const htd_cli::Option & versionOption = optionManager.accessOption("version");

    const htd_cli::Choice & outputFormatChoice = optionManager.accessChoice("output");

    const htd_cli::Choice & decompositionTypeChoice = optionManager.accessChoice("type");

    const htd_cli::Choice & strategyChoice = optionManager.accessChoice("strategy");

    const htd_cli::SingleValueOption & seedOption = optionManager.accessSingleValueOption("seed");

    const htd_cli::SingleValueOption & instanceOption = optionManager.accessSingleValueOption("instance");

    const htd_cli::Choice & optimizationChoice = optionManager.accessChoice("opt");

    const htd_cli::SingleValueOption & iterationOption = optionManager.accessSingleValueOption("iterations");

    const htd_cli::SingleValueOption & patienceOption = optionManager.accessSingleValueOption("patience");

    const htd_cli::Option & triangulationMinimizationOption = optionManager.accessOption("triangulation-minimization");

    if (ret && helpOption.used())
    {
        std::cout << "VERSION: htd_main " << htd_version() << std::endl << std::endl;

        std::cout << "USAGE: " << argv[0] << " [options...] < input" << std::endl << std::endl;

        optionManager.printHelp();

        ret = false;
    }

    if (ret && versionOption.used())
    {
        std::cout << "VERSION: htd_main " << htd_version() << std::endl << std::endl;

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
                unsigned long seed = std::stoul(value, &index, 10);

                if (index != value.length())
                {
                    std::cerr << "INVALID SEED: " << value << std::endl;

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
            srand(static_cast<unsigned int>(time(NULL)));
        }
    }

    if (ret)
    {
        if (instanceOption.used())
        {
            std::ifstream instanceStream(instanceOption.value());

            if (!instanceStream.good())
            {
                std::cerr << "INVALID INSTANCE FILE: " << instanceOption.value() << std::endl;

                ret = false;
            }
        }
    }

    if (ret && strategyChoice.used())
    {
        const std::string & value = strategyChoice.value();

        if (value == "min-fill")
        {
            manager->orderingAlgorithmFactory().setConstructionTemplate(new htd::MinFillOrderingAlgorithm(manager));
        }
        else if (value == "min-degree")
        {
            manager->orderingAlgorithmFactory().setConstructionTemplate(new htd::MinDegreeOrderingAlgorithm(manager));
        }
        else if (value == "min-separator")
        {
            if (optimizationChoice.used() && std::string(optimizationChoice.value()) == "width")
            {
                std::cerr << "INVALID DECOMPOSITION STRATEGY: Strategy \"min-separator\" may only be used when option --opt is set to \"none\"!" << std::endl;

                ret = false;
            }

            if (ret && triangulationMinimizationOption.used())
            {
                std::cerr << "INVALID USE OF PROGRAM OPTION: Triangulation minimization may only be applied when using a decomposition strategy based on vertex elimination orderings!" << std::endl;

                ret = false;
            }
        }
        else if (value == "max-cardinality")
        {
            manager->orderingAlgorithmFactory().setConstructionTemplate(new htd::MaximumCardinalitySearchOrderingAlgorithm(manager));
        }
        else if (value == "max-cardinality-enhanced")
        {
            manager->orderingAlgorithmFactory().setConstructionTemplate(new htd::EnhancedMaximumCardinalitySearchOrderingAlgorithm(manager));
        }
        else if (value == "challenge")
        {
            if (!optimizationChoice.used() || std::string(optimizationChoice.value()) != "width")
            {
                std::cerr << "INVALID DECOMPOSITION STRATEGY: Strategy \"challenge\" may only be used when option --opt is set to \"width\"!" << std::endl;

                ret = false;
            }
        }
        else if (value == "random")
        {
            manager->orderingAlgorithmFactory().setConstructionTemplate(new htd::RandomOrderingAlgorithm(manager));
        }
        else
        {
            std::cerr << "INVALID DECOMPOSITION STRATEGY: " << strategyChoice.value() << std::endl;

            ret = false;
        }
    }

    if (ret && decompositionTypeChoice.used() && std::string(decompositionTypeChoice.value()) == "hypertree")
    {
        if (outputFormatChoice.used() && std::string(outputFormatChoice.value()) == "td")
        {
            std::cerr << "INVALID OUTPUT FORMAT: Format 'td' only supports tree decompositions!" << std::endl;

            ret = false;
        }

        if (optimizationChoice.used() && std::string(optimizationChoice.value()) == "width")
        {
            std::cerr << "INVALID PROGRAM CALL: Currently, optimization is supported only for tree decompositions!" << std::endl;

            ret = false;
        }
    }

    if (ret)
    {
        if (iterationOption.used())
        {
            if (optimizationChoice.used() && std::string(optimizationChoice.value()) == "width")
            {
                std::size_t index = 0;

                const std::string & value = iterationOption.value();

                if (value.empty() || value.find_first_not_of("01234567890") != std::string::npos)
                {
                    std::cerr << "INVALID NUMBER OF ITERATIONS: " << iterationOption.value() << std::endl;

                    ret = false;
                }

                if (ret)
                {
                    std::stoul(value, &index, 10);

                    if (index != value.length())
                    {
                        std::cerr << "INVALID NUMBER OF ITERATIONS: " << value << std::endl;

                        ret = false;
                    }
                }
            }
            else
            {
                std::cerr << "INVALID PROGRAM CALL: Option --iterations may only be used when option --opt is set to \"width\"!" << std::endl;

                ret = false;
            }
        }
    }

    if (ret)
    {
        if (patienceOption.used())
        {
            if (optimizationChoice.used() && std::string(optimizationChoice.value()) == "width")
            {
                std::size_t index = 0;

                const std::string & value = patienceOption.value();

                if (value.empty() || (value != "-1" && value.find_first_not_of("01234567890") != std::string::npos))
                {
                    std::cerr << "INVALID LEVEL OF PATIENCE: " << patienceOption.value() << std::endl;

                    ret = false;
                }

                if (ret && value != "-1")
                {
                    std::stoul(value, &index, 10);

                    if (index != value.length())
                    {
                        std::cerr << "INVALID LEVEL OF PATIENCE: " << value << std::endl;

                        ret = false;
                    }
                }
            }
            else
            {
                std::cerr << "INVALID PROGRAM CALL: Option --patience may only be used when option --opt is set to \"width\"!" << std::endl;

                ret = false;
            }
        }
    }

    if (ret && triangulationMinimizationOption.used())
    {
        htd::TriangulationMinimizationOrderingAlgorithm * algorithm =
            new htd::TriangulationMinimizationOrderingAlgorithm(libraryInstance);

        algorithm->setOrderingAlgorithm(manager->orderingAlgorithmFactory().createInstance());

        manager->orderingAlgorithmFactory().setConstructionTemplate(algorithm);
    }

    return ret;
}

template <typename DecompositionAlgorithm, typename GraphType, typename Exporter>
void decompose(const htd::LibraryInstance & instance, const DecompositionAlgorithm & algorithm, GraphType * graph, const Exporter & exporter)
{
    if (graph != nullptr && !instance.isTerminated())
    {
        auto * decomposition = algorithm.computeDecomposition(*graph);

        if (decomposition != nullptr)
        {
            if (!instance.isTerminated() || algorithm.isSafelyInterruptible())
            {
                exporter.write(*decomposition, *graph, std::cout);
            }
            else
            {
                std::cerr << "Program was terminated successfully!" << std::endl;
            }

            delete decomposition;
        }
        else
        {
            if (instance.isTerminated())
            {
                std::cerr << "Program was terminated successfully!" << std::endl;
            }
            else
            {
                std::cerr << "NO TREE DECOMPOSITION COMPUTED!" << std::endl;
            }
        }

        delete graph;
    }
    else
    {
        if (instance.isTerminated())
        {
            std::cerr << "Program was terminated successfully!" << std::endl;
        }
        else
        {
            std::cerr << "NO VALID INSTANCE PROVIDED!" << std::endl;
        }
    }
}

template <typename DecompositionAlgorithm, typename GraphType, typename Exporter>
void decomposeNamed(const htd::LibraryInstance & instance, const DecompositionAlgorithm & algorithm, GraphType * graph, const Exporter & exporter)
{
    if (graph != nullptr && !instance.isTerminated())
    {
        auto * decomposition = algorithm.computeDecomposition(graph->internalGraph());

        if (decomposition != nullptr)
        {
            if (!instance.isTerminated() || algorithm.isSafelyInterruptible())
            {
                exporter.write(*decomposition, *graph, std::cout);
            }
            else
            {
                std::cerr << "Program was terminated successfully!" << std::endl;
            }

            delete decomposition;
        }
        else
        {
            if (instance.isTerminated())
            {
                std::cerr << "Program was terminated successfully!" << std::endl;
            }
            else
            {
                std::cerr << "NO TREE DECOMPOSITION COMPUTED!" << std::endl;
            }
        }

        delete graph;
    }
    else
    {
        if (instance.isTerminated())
        {
            std::cerr << "Program was terminated successfully!" << std::endl;
        }
        else
        {
            std::cerr << "NO VALID INSTANCE PROVIDED!" << std::endl;
        }

        if (graph != nullptr)
        {
            delete graph;
        }
    }
}

template <typename DecompositionAlgorithm, typename Exporter>
void run(const DecompositionAlgorithm & algorithm, const Exporter & exporter, const std::string & inputFormat, const htd::LibraryInstance * const manager)
{
    if (inputFormat == "gr")
    {
        htd_io::GrFormatImporter importer(manager);

        decompose(*manager, algorithm, importer.import(std::cin), exporter);
    }
    else if (inputFormat == "lp")
    {
        htd_io::LpFormatImporter importer(manager);

        decomposeNamed(*manager, algorithm, importer.import(std::cin), exporter);
    }
    else if (inputFormat == "hgr")
    {
        htd_io::HgrFormatImporter importer(manager);

        decompose(*manager, algorithm, importer.import(std::cin), exporter);
    }
}

template <typename DecompositionAlgorithm, typename Exporter>
void run(const DecompositionAlgorithm & algorithm, const Exporter & exporter, const std::string & inputFormat, const htd::LibraryInstance * const manager, const std::string & instanceFile)
{
    if (inputFormat == "gr")
    {
        htd_io::GrFormatImporter importer(manager);

        decompose(*manager, algorithm, importer.import(instanceFile), exporter);
    }
    else if (inputFormat == "lp")
    {
        htd_io::LpFormatImporter importer(manager);

        decomposeNamed(*manager, algorithm, importer.import(instanceFile), exporter);
    }
    else if (inputFormat == "hgr")
    {
        htd_io::HgrFormatImporter importer(manager);

        decompose(*manager, algorithm, importer.import(instanceFile), exporter);
    }
}

void handleSignal(int signal)
{
    switch (signal)
    {
        case SIGINT:
        {
            libraryInstance->terminate();

            break;
        }
        case SIGTERM:
        {
            libraryInstance->terminate();

            break;
        }
        default:
        {
            break;
        }
    }
}

int main(int argc, const char * const * const argv)
{
    int ret = 0;

    bool error = false;

    std::ios_base::sync_with_stdio(false);

    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    htd_cli::OptionManager * optionManager = createOptionManager();

    if (optionManager != nullptr && handleOptions(argc, argv, *optionManager, libraryInstance))
    {
        const htd_cli::Choice & inputFormatChoice = optionManager->accessChoice("input");

        const htd_cli::Choice & outputFormatChoice = optionManager->accessChoice("output");

        const htd_cli::Choice & decompositionTypeChoice = optionManager->accessChoice("type");

        const htd_cli::Choice & strategyChoice = optionManager->accessChoice("strategy");

        const htd_cli::Choice & preprocessingChoice = optionManager->accessChoice("preprocessing");

        const htd_cli::Choice & optimizationChoice = optionManager->accessChoice("opt");

        const htd_cli::SingleValueOption & iterationOption = optionManager->accessSingleValueOption("iterations");

        const htd_cli::SingleValueOption & instanceOption = optionManager->accessSingleValueOption("instance");

        const htd_cli::SingleValueOption & patienceOption = optionManager->accessSingleValueOption("patience");

        const htd_cli::Option & printProgressOption = optionManager->accessOption("print-progress");

        const std::string & outputFormat = outputFormatChoice.value();

        bool hypertreeDecompositionRequested = decompositionTypeChoice.used() && std::string(decompositionTypeChoice.value()) == "hypertree";

        if (std::string(strategyChoice.value()) == "min-separator")
        {
            htd::SeparatorBasedTreeDecompositionAlgorithm * treeDecompositionAlgorithm = new htd::SeparatorBasedTreeDecompositionAlgorithm(libraryInstance);

            treeDecompositionAlgorithm->setComputeInducedEdgesEnabled(false);

            libraryInstance->treeDecompositionAlgorithmFactory().setConstructionTemplate(treeDecompositionAlgorithm);
        }
        else
        {
            htd::BucketEliminationTreeDecompositionAlgorithm * treeDecompositionAlgorithm = new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

            treeDecompositionAlgorithm->setComputeInducedEdgesEnabled(false);

            libraryInstance->treeDecompositionAlgorithmFactory().setConstructionTemplate(treeDecompositionAlgorithm);
        }

        if (hypertreeDecompositionRequested)
        {
            htd::IHypertreeDecompositionAlgorithm * algorithm = libraryInstance->hypertreeDecompositionAlgorithmFactory().createInstance();

            htd_io::IHypertreeDecompositionExporter * exporter = nullptr;

            if (outputFormat == "human")
            {
                exporter = new htd_io::HumanReadableExporter();
            }
            else if (outputFormat == "width")
            {
                exporter = new htd_io::WidthExporter();
            }
            else
            {
                std::cerr << "INVALID OUTPUT FORMAT: " << outputFormat << std::endl;

                error = true;
            }

            if (!error)
            {
                if (instanceOption.used())
                {
                    run(*algorithm, *exporter, inputFormatChoice.value(), libraryInstance, instanceOption.value());
                }
                else
                {
                    run(*algorithm, *exporter, inputFormatChoice.value(), libraryInstance);
                }

                delete exporter;
            }

            delete algorithm;
        }
        else
        {
            htd_io::ITreeDecompositionExporter * exporter = nullptr;

            if (outputFormat == "td")
            {
                exporter = new htd_io::TdFormatExporter();
            }
            else if (outputFormat == "human")
            {
                exporter = new htd_io::HumanReadableExporter();
            }
            else if (outputFormat == "width")
            {
                exporter = new htd_io::WidthExporter();
            }
            else
            {
                std::cerr << "INVALID OUTPUT FORMAT: " << outputFormat << std::endl;

                error = true;
            }

            if (!error)
            {
                std::size_t optimalMaximumBagSize = (std::size_t)-1;

                if (std::string(optimizationChoice.value()) == "width")
                {
                    htd::CombinedWidthMinimizingTreeDecompositionAlgorithm * algorithm = new htd::CombinedWidthMinimizingTreeDecompositionAlgorithm(libraryInstance);

                    if (std::string(strategyChoice.value()) == "challenge")
                    {
                        htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm * adaptiveAlgorithm = new htd::AdaptiveWidthMinimizingTreeDecompositionAlgorithm(libraryInstance);

                        htd::BucketEliminationTreeDecompositionAlgorithm * algorithm1 = new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

                        algorithm1->setOrderingAlgorithm(new htd::MinDegreeOrderingAlgorithm(libraryInstance));

                        adaptiveAlgorithm->addDecompositionAlgorithm(algorithm1);

                        htd::BucketEliminationTreeDecompositionAlgorithm * algorithm2 = new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

                        algorithm2->setOrderingAlgorithm(new htd::MinFillOrderingAlgorithm(libraryInstance));

                        adaptiveAlgorithm->addDecompositionAlgorithm(algorithm2);

                        htd::BucketEliminationTreeDecompositionAlgorithm * algorithm3 = new htd::BucketEliminationTreeDecompositionAlgorithm(libraryInstance);

                        algorithm3->setOrderingAlgorithm(new htd::MaximumCardinalitySearchOrderingAlgorithm(libraryInstance));

                        adaptiveAlgorithm->addDecompositionAlgorithm(algorithm3,
                                                                     [](const htd::IMultiHypergraph & graph, const htd::IPreprocessedGraph & preprocessedGraph)
                        {
                            HTD_UNUSED(graph)

                            return preprocessedGraph.vertexCount() <= 10240;
                        });

                        if (iterationOption.used())
                        {
                            std::size_t iterations = std::stoul(iterationOption.value(), nullptr, 10);

                            if (iterations == 0)
                            {
                                iterations = (std::size_t)-1;
                            }

                            adaptiveAlgorithm->setIterationCount(iterations);
                        }
                        else
                        {
                            adaptiveAlgorithm->setIterationCount(10);
                        }

                        if (patienceOption.used())
                        {
                            if (std::string(patienceOption.value()) == "-1")
                            {
                                adaptiveAlgorithm->setNonImprovementLimit((std::size_t)-1);
                            }
                            else
                            {
                                adaptiveAlgorithm->setNonImprovementLimit(std::stoul(patienceOption.value(), nullptr, 10));
                            }
                        }

                        adaptiveAlgorithm->setDecisionRounds(5);

                        algorithm->addDecompositionAlgorithm(new htd::TrivialTreeDecompositionAlgorithm(libraryInstance));

                        algorithm->addDecompositionAlgorithm(adaptiveAlgorithm);
                    }
                    else
                    {
                        htd::WidthMinimizingTreeDecompositionAlgorithm * baseAlgorithm = new htd::WidthMinimizingTreeDecompositionAlgorithm(libraryInstance);

                        if (iterationOption.used())
                        {
                            std::size_t iterations = std::stoul(iterationOption.value(), nullptr, 10);

                            if (iterations == 0)
                            {
                                iterations = (std::size_t)-1;
                            }

                            baseAlgorithm->setIterationCount(iterations);
                        }
                        else
                        {
                            baseAlgorithm->setIterationCount(10);
                        }

                        if (patienceOption.used())
                        {
                            if (std::string(patienceOption.value()) == "-1")
                            {
                                baseAlgorithm->setNonImprovementLimit((std::size_t)-1);
                            }
                            else
                            {
                                baseAlgorithm->setNonImprovementLimit(std::stoul(patienceOption.value(), nullptr, 10));
                            }
                        }

                        algorithm->addDecompositionAlgorithm(baseAlgorithm);
                    }

                    algorithm->setComputeInducedEdgesEnabled(false);

                    libraryInstance->treeDecompositionAlgorithmFactory().setConstructionTemplate(algorithm);
                }

                htd::GraphPreprocessor * preprocessor = new htd::GraphPreprocessor(libraryInstance);

                if (std::string(preprocessingChoice.value()) == "none")
                {
                    preprocessor->setPreprocessingStrategy(0);
                }
                else if (std::string(preprocessingChoice.value()) == "simple")
                {
                    preprocessor->setPreprocessingStrategy(1);
                }
                else if (std::string(preprocessingChoice.value()) == "advanced")
                {
                    preprocessor->setPreprocessingStrategy(2);
                }
                else if (std::string(preprocessingChoice.value()) == "full")
                {
                    preprocessor->setPreprocessingStrategy(3);

                    preprocessor->setIterationCount(256);
                    preprocessor->setNonImprovementLimit(64);
                }

                htd_io::IGraphToTreeDecompositionProcessor * processor = nullptr;

                if (std::string(inputFormatChoice.value()) == "gr")
                {
                    processor = new htd_io::GrFormatGraphToTreeDecompositionProcessor(libraryInstance);
                }
                else if (std::string(inputFormatChoice.value()) == "hgr")
                {
                    processor = new htd_io::HgrFormatGraphToTreeDecompositionProcessor(libraryInstance);
                }
                else if (std::string(inputFormatChoice.value()) == "lp")
                {
                    processor = new htd_io::LpFormatGraphToTreeDecompositionProcessor(libraryInstance);
                }
                else
                {
                    std::cerr << "INVALID INPUT FORMAT: " << inputFormatChoice.value() << std::endl;

                    std::exit(1);
                }

                processor->setExporter(exporter);

                processor->setPreprocessor(preprocessor);

                std::chrono::milliseconds::rep start =
                    std::chrono::duration_cast<std::chrono::milliseconds>
                        (std::chrono::system_clock::now().time_since_epoch()).count();

                std::chrono::milliseconds::rep lastStepFinished = start;

                if (printProgressOption.used())
                {
                    processor->registerParsingCallback([&](htd_io::parsing_result_t result, std::size_t vertexCount, std::size_t edgeCount){
                        lastStepFinished =
                            std::chrono::duration_cast<std::chrono::milliseconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();

                        if (result == htd_io::ParsingResult::OK)
                        {
                            if (outputFormat == "td")
                            {
                                std::cout << "c progress PARSING COMPLETED " << lastStepFinished << std::endl;
                            }
                            else
                            {
                                std::ios::fmtflags oldflags(std::cout.flags());

                                std::cout << "Parsing completed:" << std::endl;
                                std::cout << "   Duration:         " << std::right << std::setw(15) << std::fixed << std::setprecision(3) << ((lastStepFinished - start) / 1000.0) << " s" << std::endl;
                                std::cout << "   - - - - - - - - - - - - - - - - - -" << std::endl;
                                std::cout << "   Vertices:         " << std::right << std::setw(17) << vertexCount << std::endl;
                                std::cout << "   Hyperedges:       " << std::right << std::setw(17) << edgeCount << std::endl;
                                std::cout << std::endl;

                                std::cout.flags(oldflags);
                            }
                        }
                        else
                        {
                            if (outputFormat == "td")
                            {
                                std::cout << "c progress PARSING FAILED " << lastStepFinished << std::endl;
                            }
                            else
                            {
                                std::ios::fmtflags oldflags(std::cout.flags());

                                std::cout << "Parsing failed:" << std::endl;
                                std::cout << "   Duration:         " << std::right << std::setw(15) << std::fixed << std::setprecision(3) << ((lastStepFinished - start) / 1000.0) << " s" << std::endl;
                                std::cout << "   - - - - - - - - - - - - - - - - - -" << std::endl;
                                std::cout << std::endl;

                                std::cout.flags(oldflags);
                            }
                        }
                    });

                    if (std::string(preprocessingChoice.value()) != "none")
                    {
                        processor->registerPreprocessingCallback([&](std::size_t vertexCount, std::size_t edgeCount){
                            std::chrono::milliseconds::rep msSinceEpoch =
                                std::chrono::duration_cast<std::chrono::milliseconds>
                                    (std::chrono::system_clock::now().time_since_epoch()).count();

                            if (outputFormat == "td")
                            {
                                std::cout << "c progress PREPROCESSING FINISHED " << msSinceEpoch << std::endl;
                            }
                            else
                            {
                                std::ios::fmtflags oldflags(std::cout.flags());

                                std::cout << "Preprocessing finished:" << std::endl;
                                std::cout << "   Duration:         " << std::right << std::setw(15) << std::fixed << std::setprecision(3) << ((msSinceEpoch - lastStepFinished) / 1000.0) << " s" << std::endl;
                                std::cout << "   - - - - - - - - - - - - - - - - - -" << std::endl;
                                std::cout << "   Vertices:         " << std::right << std::setw(17) << vertexCount << std::endl;
                                std::cout << "   Hyperedges:       " << std::right << std::setw(17) << edgeCount << std::endl;
                                std::cout << std::endl;

                                std::cout.flags(oldflags);
                            }

                            lastStepFinished = msSinceEpoch;
                        });
                    }

                    processor->registerDecompositionCallback([&](const htd::FitnessEvaluation & fitness){
                        std::chrono::milliseconds::rep msSinceEpoch =
                            std::chrono::duration_cast<std::chrono::milliseconds>
                                (std::chrono::system_clock::now().time_since_epoch()).count();

                        if (outputFormat != "td")
                        {
                            std::ios::fmtflags oldflags(std::cout.flags());

                            std::cout << "New decomposition computed:" << std::endl;
                            std::cout << "   Duration:         " << std::right << std::setw(15) << std::fixed << std::setprecision(3) << ((msSinceEpoch - lastStepFinished) / 1000.0) << " s" << std::endl;
                            std::cout << "   - - - - - - - - - - - - - - - - - -" << std::endl;

                            std::cout.flags(oldflags);
                        }

                        std::size_t maximumBagSize = static_cast<std::size_t>(-fitness.at(0));

                        if (maximumBagSize < optimalMaximumBagSize)
                        {
                            optimalMaximumBagSize = maximumBagSize;

                            std::chrono::milliseconds::rep msSinceEpoch =
                                std::chrono::duration_cast<std::chrono::milliseconds>
                                    (std::chrono::system_clock::now().time_since_epoch()).count();

                            if (outputFormat == "td")
                            {
                                std::cout << "c status " << optimalMaximumBagSize << " " << msSinceEpoch << std::endl;
                            }
                            else
                            {
                                std::ios::fmtflags oldflags(std::cout.flags());

                                std::cout << "   Improved Maximum Bag Size: " << std::right << std::setw(8) << optimalMaximumBagSize << std::endl;

                                std::cout.flags(oldflags);
                            }
                        }

                        if (outputFormat != "td")
                        {
                            std::cout << std::endl;
                        }

                        lastStepFinished = msSinceEpoch;
                    });
                }

                if (instanceOption.used())
                {
                    processor->process(instanceOption.value(), std::cout);
                }
                else
                {
                    processor->process();
                }

                delete processor;
            }
        }
    }

    delete libraryInstance;

    if (optionManager != nullptr)
    {
        delete optionManager;
    }

    return ret;
}
