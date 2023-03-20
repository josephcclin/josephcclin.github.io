import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name} from "./chessboard_utils.js";

let boards = initializeBoards([
    ["board-uniform-crossover-1", "#uniform-crossover-1"],
    ["board-uniform-crossover-2", "#uniform-crossover-2"],
    ["board-uniform-crossover-3", "#uniform-crossover-3"],
]);


// initialize crossover result
let vector1 = createVector(position_to_column_vector(boards[0].position()), "#uniform-crossover-1b");
let vector2 = createVector(position_to_column_vector(boards[1].position()), "#uniform-crossover-2b");
let divsParent1 = $(vector1).find("div");
let divsParent2 = $(vector2).find("div");
let divsChild = $("#uniform-crossover-3").find("div");

let currentVector = [];
for (let i = 0; i < 8; i++)
{
    currentVector[i] = 0.5 >= Math.random();
}

divsParent1.click(function(){
    currentVector[this.getAttribute("childindex")]=false;
    update_child(currentVector, divsParent1, divsParent2, divsChild)
});

divsParent2.click(function(){
    currentVector[this.getAttribute("childindex")]=true;
    update_child(currentVector, divsParent1, divsParent2, divsChild)
});

update_child(currentVector, divsParent1, divsParent2, divsChild);

function update_child(currentVector, divsParent1, divsParent2, divsChild){
    let newVector = [];
    for (let i = 0; i < 8; i++){
        if (currentVector[i] < 0.5){
            // read value
            newVector[i] = 8-parseInt(divsParent1[i].innerHTML);

            //newVector[i] = $(vector2).find("div")[i].style.backgroundColor = "#ffffff";
            divsParent2[i].classList.add("inactive");
            divsParent2[i].classList.remove("active");

            divsParent1[i].classList.add("active");
            divsParent1[i].classList.remove("inactive");

            const style = getComputedStyle(divsParent1[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        } else {
            // read value
            newVector[i] = 8-parseInt(divsParent2[i].innerHTML);

            divsParent2[i].classList.add("active");
            divsParent2[i].classList.remove("inactive");

            divsParent1[i].classList.add("inactive");
            divsParent1[i].classList.remove("active");

            const style = getComputedStyle(divsParent2[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        }

        divsChild[i].innerHTML = 8-newVector[i];
    }
    //console.log(newVector, column_vector_to_position(newVector));

    boards[2].position(column_vector_to_position(newVector));
}

function updateVectors(value, divsParent1, divsParent2){
    //retrieve the x first elements
    let newVector = [];
    for (let i = 0; i < 8; i++){
        if (i < value){
            // read value
            newVector[i] = 8-parseInt(divsParent1[i].innerHTML);

            //newVector[i] = $(vector2).find("div")[i].style.backgroundColor = "#ffffff";
            divsParent2[i].classList.add("inactive");
            divsParent2[i].classList.remove("active");

            divsParent1[i].classList.add("active");
            divsParent1[i].classList.remove("inactive");

            const style = getComputedStyle(divsParent1[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        } else {
            // read value
            newVector[i] = 8-parseInt(divsParent2[i].innerHTML);

            divsParent2[i].classList.add("active");
            divsParent2[i].classList.remove("inactive");

            divsParent1[i].classList.add("inactive");
            divsParent1[i].classList.remove("active");

            const style = getComputedStyle(divsParent2[i]);
            divsChild[i].style.backgroundColor = style["background-color"];
        }

        divsChild[i].innerHTML = 8-newVector[i];
    }
    //console.log(newVector, column_vector_to_position(newVector));

    boards[2].position(column_vector_to_position(newVector));
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




