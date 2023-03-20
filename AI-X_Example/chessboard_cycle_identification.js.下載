import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, random_permutation} from "./chessboard_utils.js";

// initialize crossover result
let vector1 = createVector([1, 3, 6, 4, 8, 7, 2, 5], "#cycle-crossover-parent-1");
let vector2 = createVector([4, 2, 1, 6, 7, 3, 8, 5], "#cycle-crossover-parent-2");
let cycle_vector = createVector(["","","","","","","",""], "#cycle-crossover-cycle-vector");
let divsParent1 = $(vector1).find("div");
let divsParent2 = $(vector2).find("div");
let divsCycles = $(cycle_vector).find("div");

//updateVectors(rangeInput.getAttribute("value"), divsParent1, divsParent2);
let step = 0;
let step_description = []
let cycles = []
cycle_detection(divsParent1, divsParent2, divsCycles);

//console.log(step_description)

let startbutton = $("#cycle-start");
let backbutton = $("#cycle-back");
let nextbutton = $("#cycle-next");
let endbutton = $("#cycle-end");
let description = $("#cycle-identification-text").get()[0];

startbutton.click(function(){
    step = 0;
    for (let i = 1; i < 8; i++){
        divsCycles[i].style.color = "white";
    }
    update_description()
})

backbutton.click(function(){
    if (step_description[step].includes("found at index")){
        let i = step_description[step].split("found at index")[1].split(".")[0];
        divsCycles[Number(i)-1].style.color = "white";
    }
    if (step_description[step].includes("Start the new cycle at index ")) {
        let i = step_description[step].split("Start the new cycle at index ")[1].split(".")[0];
        divsCycles[Number(i)-1].style.color = "white";
    }
    step--;
    update_description()
})

nextbutton.click(function(){
    step++;
    if (step_description[step].includes("found at index")){
        let i = step_description[step].split("found at index")[1].split(".")[0];
        divsCycles[Number(i)-1].style.color = "black";
    }
    if (step_description[step].includes("Start the new cycle at index ")) {
        let i = step_description[step].split("Start the new cycle at index ")[1].split(".")[0];
        divsCycles[Number(i)-1].style.color = "black";
    }

    update_description()
})

endbutton.click(function(){
    step = step_description.length-1;

    for (let i = 0; i < 8; i++){
        divsCycles[Number(i)].style.color = "black";
    }
    update_description()
})

update_description();
for (let i = 1; i < 8; i++){
    divsCycles[i].style.color = "white";
}

function update_description(){
    //console.log(step);
    //console.log(step_description[step]);

    description.innerHTML = step_description[step];

    if (step === step_description.length-1){
        nextbutton.prop('disabled', true);
        endbutton.prop('disabled', true);
    } else {
        nextbutton.prop('disabled', false);
        endbutton.prop('disabled', false);
    }
    if (step === 0){
        startbutton.prop('disabled', true);
        backbutton.prop('disabled', true);
    } else {
        startbutton.prop('disabled', false);
        backbutton.prop('disabled', false);
    }
}

function cycle_detection(divsParent1, divsParent2, divsCycles){
    let parent1 = [];
    let parent2 = [];
    for (let i = 0; i < 8; i++){
        parent1[i] = parseInt(divsParent1[i].innerHTML);
        parent2[i] = parseInt(divsParent2[i].innerHTML);
        cycles[i] = 0;
    }

    let cycleNumber = 1;
    for (let i = 0; i < 8; i++){
        if (cycles[i] === 0){
            step_description = step_description.concat("Start the new cycle at index " + (i+1) + ". Search for value " + parent1[i] + " in Parent 2. ")
            let cycle_indices = get_cycle_indices(i, parent1, parent2);
            step_description = step_description.concat("Value "+ parent1[cycle_indices.length - 1] + " found at index "+ (i+1) + ". Cycle " + (cycleNumber) + " complete. Mark cycle indices in cycle vector.")
            for (let index in cycle_indices)
            {
                cycles[cycle_indices[index]] = cycleNumber;
            }
            cycleNumber++;
        }
    }
    step_description = step_description.concat("All indices are part of a cycle. Algorithm completed.")

    for (let i = 0; i < 8; i++){
        divsCycles[i].innerHTML = cycles[i];
    }
}

function get_cycle_indices(start_index, parent1, parent2){
    let cycle_indices = [start_index];
    let current_value = null;
    let current_index = start_index;
    while (true){
        current_value = parent1[current_index];
        current_index = parent2.indexOf(current_value);

        if (current_index === start_index) {
            return cycle_indices;
        }

        cycle_indices = cycle_indices.concat([current_index]);
        step_description = step_description.concat("Value "+ current_value + " found at index "+ (current_index+1) + ". Add index " + (current_index+1) + " to current cycle. Next, search for value " + parent1[current_index] + " in Parent 2.")
    }
}




