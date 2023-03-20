import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, createMatrix} from "./chessboard_utils.js";
import {position_to_binary_board, binary_board_to_position} from "./chessboard_utils.js";

let boards = initializeBoards([
    ["board-matrix-crossover-1", "#matrix-crossover-1"],
    ["board-matrix-crossover-2", "#matrix-crossover-2"],
    ["board-matrix-crossover-3", "#matrix-crossover-3"],
]);


// initialize crossover result
//let matrix1 = createMatrix(position_to_binary_board(boards[0].position())[0], "#matrix-crossover-1b");
//let matrix2 = createMatrix(position_to_binary_board(boards[1].position())[0], "#matrix-crossover-2b");
//let divsOriginal1 = $(boards[0].table).find("div");
//let divsOriginal2 = $(boards[1].table).find("div");
let divsParent1 = $(boards[0].table).find("div");
let divsParent2 = $(boards[1].table).find("div");
let divsChild = $("#matrix-crossover-3").find("div");

var rangeInput = document.getElementById("myRangeMatrix");
updateMatrices(rangeInput.getAttribute("value"), divsParent1, divsParent2);


rangeInput.addEventListener("input", function(e) {
    updateMatrices(e.target.value, divsParent1, divsParent2);
}, false);


function updateMatrices(value, divsParent1, divsParent2){
    //retrieve the x first elements
    let inactiveBackgroundColor = "#ffffff";
    let inactiveColor = "lightgray";

    let binary_board = [];
    for (let i = 0; i < 8; i++){
        let current_row = [];
        if (i < value){
            //newVector[i] = $(vector2).find("div")[i].style.backgroundColor = "#ffffff";
            for (let j = 0; j < 8; j++){
                // style active parent
                let style = getComputedStyle(divsParent1[i+j*8]);
                divsParent1[i+j*8].style.backgroundColor = null;
                divsParent1[i+j*8].style.color = null;
                divsParent1[i+j*8].style.backgroundColor = style["background-color"];

                // style inactive parent
                divsParent2[i+j*8].style.backgroundColor = inactiveBackgroundColor;
                divsParent2[i+j*8].style.color = inactiveColor;

                // style child
                divsChild[i+j*8].style.backgroundColor = style["background-color"];
                divsChild[i+j*8].innerHTML = divsParent1[i+j*8].innerHTML;

                // set value
                current_row[j] = divsParent1[i+j*8].innerHTML
            }
        } else {
            for (let j = 0; j < 8; j++) {
                // style active parent
                let style = getComputedStyle(divsParent2[i+j*8]);
                divsParent2[i+j*8].style.backgroundColor = null;
                divsParent2[i+j*8].style.color = null;
                divsParent2[i+j*8].style.backgroundColor = style["background-color"];

                // style inactive parent
                divsParent1[i+j*8].style.backgroundColor = inactiveBackgroundColor;
                divsParent1[i+j*8].style.color = inactiveColor;

                // style child
                divsChild[i+j*8].style.backgroundColor = style["background-color"];
                divsChild[i+j*8].innerHTML = divsParent2[i+j*8].innerHTML;

                // set value
                current_row[j] = divsParent2[i+j*8].innerHTML
            }
        }
        binary_board[i] = current_row;
    }
    //console.log(newVector, column_vector_to_position(newVector));
    let pos = binary_board_to_position(binary_board);
    boards[2].position(pos);
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
        let table = createMatrix(position_to_binary_board(board.position())[0], vectorContainer);
        //createVector(position_to_column_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen(this, board);});
        board.table = table;
        boards[i] = board;
    }
    return boards;
}





