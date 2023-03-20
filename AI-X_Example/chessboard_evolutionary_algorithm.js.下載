import {
    highlightCollisions,
    example_positions,
    position_to_binary_board,
    column_vector_to_position
} from "./chessboard_utils.js";
import {RowVectorIndividual, validateRowVectorIndividual, RowVectorMutationOptions, RowVectorCrossoverOptions} from "./rowVectorIndiduals.js"
import {ColumnVectorIndividual, validateColumnVectorIndividual, ColumnVectorCrossoverOptions, ColumnVectorMutationOptions} from "./columnVectorIndividuals.js"
import {ConstrainedMatrixIndividual, validateConstrainedMatrixIndividual, ConstrainedMatrixCrossoverOptions, ConstrainedMatrixMutationOptions} from "./constrainedMatrixIndividuals.js"
import {PermutationIndividual, validatePermutationIndividual, PermutationVectorMutationOptions, PermutationVectorCrossoverOptions} from "./permutationIndividual.js"

(function($, window) {
    $.fn.replaceOptions = function(options) {
        var self, $option;

        this.empty();
        self = this;

        $.each(options, function(index, option) {
            $option = $("<option></option>")
                .attr("value", option.value)
                .text(option.text);
            self.append($option);
        });
    };
})(jQuery, window);

let board = Chessboard('board-ea-result', {
    draggable: false,
    //position: example_positions[0],
});

document.getElementById("run-ea-button").addEventListener("click", runEA);
$('#select_representation').change(function () {updateGUI()} );
updateGUI();


function runEA(){
    let representationName = $('#select_representation').find(":selected").text();
    let mutationName = $('#select_mutation').find(":selected").text();
    let crossoverName = $('#select_crossover').find(":selected").text();

    let repetitions = 1;
    let solvedRuns = 0;
    let totalGenerations = 0;
    for (let i = 0; i < repetitions; i++){
        let result = runEvolutionaryAlgorithm(representationName, mutationName, crossoverName);
        if (result[0]) solvedRuns += 1;
        totalGenerations += result[1];
    }
}

function runExtensive(representationName, mutationName, crossoverName){
    let repetitions = 1000;

    let solvedRuns = 0;
    let totalFitness = 0;
    let totalGenerations = 0;
    for (let i = 0; i < repetitions; i++) {
        if (i % 100 === 0)
            console.log("run", i);
        let result = runEvolutionaryAlgorithm(representationName, mutationName, crossoverName);
        if (result[0]) solvedRuns += 1;
        totalGenerations += result[2];
        totalFitness += result[1];
    }
    console.log(representationName, mutationName, crossoverName, "solved:", solvedRuns, "average fitness",
        totalFitness/repetitions, "average generations", totalGenerations / repetitions);
}


function updateGUI(){
    console.log("updateGUI")
    let representationName = $('#select_representation').find(":selected").text();

    var $selectMutation = $("#select_mutation");
    var $selectCrossover = $("#select_crossover");

    let mutations = []
    let crossovers = []

    switch (representationName){
        case "Constrained Matrix":
            mutations = ConstrainedMatrixMutationOptions;
            crossovers = ConstrainedMatrixCrossoverOptions;
            break;
        case "Row Vector":
            mutations = RowVectorMutationOptions;
            crossovers = RowVectorCrossoverOptions;
            break;
        case "Column Vector":
            mutations = ColumnVectorMutationOptions;
            crossovers = ColumnVectorCrossoverOptions;
            break;
        case "Permutation Vector":
            mutations = PermutationVectorMutationOptions;
            crossovers = PermutationVectorCrossoverOptions;
            break;
    }

    $selectMutation.replaceOptions(mutations.map((x, i) => {return {text: x, value: i+1};}));
    $selectCrossover.replaceOptions(crossovers.map((x, i) => {return {text: x, value: i+1};}));
}


function runEvolutionaryAlgorithm(representationName, mutationName, crossoverName){
    /*console.log(representationName);
    console.log(mutationName);
    console.log(crossoverName);*/

    let alert = $( "#alert" )
    let success = $( "#success" )
    alert.get()[0].style.display = "none"
    success.get()[0].style.display = "none"

    // parameters
    let populationsize = 10;
    let maxGenerations = 1000;
    let generations = [];

    // initialization
    let currentPopulation = initializePopulation(populationsize, representationName, mutationName, crossoverName);
    generations[0] = currentPopulation;

    //
    function checkSolved(population) {
        let solved = false;
        population.forEach(individual => {
            if (individual.fitness === 8){
                solved = true;
            }
        })
        return solved;
    }

    while (checkSolved(currentPopulation) === false && generations.length !== maxGenerations) {


        //console.log(currentPopulation.map(el => el.getFitness()))
        let mutationChilds = []

        let selectedIndividuals = tournamentSelection(currentPopulation, populationsize);
        selectedIndividuals.forEach(el => {
            let newEl = el.clone()
            newEl.mutation();
            mutationChilds[mutationChilds.length] = newEl;
        })

        let crossOverChilds = []
        for (let i = 0; i < 10; i++){
            let parent1 = selectedIndividuals[Math.floor(Math.random()*10)];
            let parent2 = selectedIndividuals[Math.floor(Math.random()*10)];

            crossOverChilds[crossOverChilds.length] = parent1.crossover(parent2);
        }

        let children = mutationChilds.concat(crossOverChilds);
        children.sort((a,b) => (a.fitness > b.fitness) ? -1 : ((b.fitness > a.fitness) ? 1 : 0))
        //console.log("children: " + children.map(el => el.getFitness()))

        currentPopulation = children.slice(0, populationsize);
        generations[generations.length] = currentPopulation;
    }
    if (!checkSolved(currentPopulation))
    {
        alert.get()[0].style.display = "block"
        success.get()[0].style.display = "none"
    } else {
        alert.get()[0].style.display = "none"
        success.get()[0].style.display = "block"
        success.children()[0].textContent = "Found a solution after " + generations.length + " generations."
    }

    currentPopulation.sort((a,b) => (a.fitness > b.fitness) ? -1 : ((b.fitness > a.fitness) ? 1 : 0))

    let pos = currentPopulation[0].getPosition()
    board.position(pos);
    highlightCollisions($("#board-ea-result"), pos);


    //console.log("currentPopulation: " + currentPopulation.map(el => el.fitness))
    //console.log("the puzzle has been solved: " + checkSolved(currentPopulation) +" after " + generations.length +" generations");
    return [checkSolved(currentPopulation), currentPopulation[0].fitness, generations.length]
}


function tournamentSelection(population, populationsize) {
    let tournamentsize = 4;
    let selectedIndividuals = [];

    function getRandomSubarray(arr, size) {
        var shuffled = arr.slice(0), i = arr.length, temp, index;
        while (i--) {
            index = Math.floor((i + 1) * Math.random());
            temp = shuffled[index];
            shuffled[index] = shuffled[i];
            shuffled[i] = temp;
        }
        return shuffled.slice(0, size);
    }

    for (let i = 0; i < populationsize; i++){
        let tournament = getRandomSubarray(population, tournamentsize);
        tournament.sort((a,b) => (a.fitness > b.fitness) ? -1 : ((b.fitness > a.fitness) ? 1 : 0))
        selectedIndividuals[i] = tournament[0].clone();
    }
    return selectedIndividuals;
}

function initializePopulation(populationsize, representationName, mutationName, crossoverName){
    let population = []
    for (let i = 0; i < populationsize; i++){
        switch (representationName){
            case "Constrained Matrix":
                population[i] = new ConstrainedMatrixIndividual(mutationName, crossoverName);
                break;
            case "Row Vector":
                population[i] = new RowVectorIndividual(mutationName, crossoverName);
                break;
            case "Column Vector":
                population[i] = new ColumnVectorIndividual(mutationName, crossoverName);
                break;
            case "Permutation Vector":
                population[i] = new PermutationIndividual(mutationName, crossoverName);
                break;
            default:
                break;
        }
    }
    return population
}


