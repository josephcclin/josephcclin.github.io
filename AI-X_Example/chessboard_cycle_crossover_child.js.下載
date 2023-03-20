import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, random_permutation} from "./chessboard_utils.js";

let boards = initializeBoards([
    ["board-cycle-crossover", "#cycle-crossover-child-vectorb"],
]);

// initialize crossover result
let vector1 = createVector([1, 3, 6, 4, 8, 7, 2, 5], "#cycle-crossover-parent-1b");
let vector2 = createVector([4, 2, 1, 6, 7, 3, 8, 5], "#cycle-crossover-parent-2b");
let cycle_vector = createVector(["","","","","","","",""], "#cycle-crossover-cycle-vectorb");
let divsParent1 = $(vector1).find("div");
let divsParent2 = $(vector2).find("div");
let divsChild = $("#cycle-crossover-child-vectorb").find("div");
let divsCycles = $(cycle_vector).find("div");

let step = 0;
let step_description = []
let cycles = []

//updateVectors(rangeInput.getAttribute("value"), divsParent1, divsParent2);
cycle_detection(divsParent1, divsParent2, divsCycles);
updateChild(divsParent1, divsParent2, divsCycles, divsChild, boards[0]);

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
            let cycle_indices = get_cycle_indices(i, parent1, parent2);
            for (let index in cycle_indices)
            {
                cycles[cycle_indices[index]] = cycleNumber;
            }
            cycleNumber++;
        }
    }

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
    }
}

function updateChild(divsParent1, divsParent2, divsCycles, divsChild, board){
    //retrieve the x first elements#

    let childVector = [];
    for (let i = 0; i < 8; i++){
        if ((parseInt(divsCycles[i].innerHTML) % 2) === 1) {
            divsChild[i].innerHTML = divsParent1[i].innerHTML;
            childVector[i] = 8-parseInt(divsParent1[i].innerHTML);

            const style = getComputedStyle(divsParent1[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        } else {
            divsChild[i].innerHTML = divsParent2[i].innerHTML;
            childVector[i] = 8-parseInt(divsParent2[i].innerHTML);

            const style = getComputedStyle(divsParent2[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        }
    }

    board.position(column_vector_to_position(childVector));
}


function initializeBoards(boardContainers){
    let boards = [];
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i][0];
        let vectorContainer = boardContainers[i][1];
        let randomPosition = random_vector();
        //console.log(randomPosition)

        //console.log(boardContainer);
        let board = Chessboard(boardContainer, {
            draggable: false,
            position: column_vector_to_position(randomPosition),
            showNotation: false,
        });
        if (board === null)
            console.log(boardContainer);
        let table = createVector(position_to_column_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen(this, board);});
        boards[i] = board;
    }
    return boards;
}






