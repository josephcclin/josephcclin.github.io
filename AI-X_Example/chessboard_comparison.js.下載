import {squareClass, position_to_binary_board, field_to_index, index_to_field, example_positions,
    highlightCollisions} from "./chessboard_utils.js";
import {createVector, position_to_row_vector} from "./chessboard_utils.js";
import {position_to_column_vector} from "./chessboard_utils.js";

// setup board
let board = Chessboard('board-comparison-board', {
    draggable: true,
    position: example_positions[0],
    onDrop: onDrop,
    onSnapbackEnd: onSnapback
});
let $board = $('#board-8-queens-matrix');

// create matrix representation
let matrix = createMatrix(position_to_binary_board(board.position())[0], "#board-comparison-8-queens");
let matrixdivs = $(matrix).find("div");
//highlightCollisions($board, board.position());

let tableRow = createVector(position_to_row_vector(board.position()), "#board-comparison-row");
let tableColumn = createVector(position_to_column_vector(board.position()), "#board-comparison-column");
let tablePermutation = createVector(position_to_column_vector(board.position()), "#board-comparison-permutation");
updateStyle();

function updateStyle(){
    $("div", matrix).each(function(){
        if (parseInt(this.innerHTML) === 1){
            this.style.backgroundColor = "#000000";
            this.style.color = "#ffffff";

        } else {
            this.style.backgroundColor = null;
            this.style.color = null;
        }
    })
}



/**
 *
 * @param board
 * @param chessfield
 * @param linkedmatrix
 */
function onDrop(source, target, piece, newPos, oldPos, orientation){
    if (target in oldPos || target === "offboard"){
        return 'snapback';
    }

    const fieldTarget = field_to_index(target);
    const fieldSource = field_to_index(source);
    const position = board.position();

    delete position[source];
    position[target] = "bQ";

    board.position(position);

    updateMatrix(fieldSource, fieldTarget);
    updateColumnVector(newPos);
    updateRowVector(newPos);
    updatePermutationVector(newPos);
    updateStyle();
}

function updateMatrix(fieldSource, fieldTarget){
    matrixdivs[fieldSource].innerHTML = 0; // update matrix
    matrixdivs[fieldTarget].innerHTML = 1; // update matrix
}

function updateColumnVector(){
    let column_vector = position_to_column_vector(board.position());
    //check feasibility
    let feasible = true;
    for (let i = 0; i < 8; i++){
        if (column_vector[i] === -1){
            feasible = false;
            break;
        }
    }

    if (feasible){
        $("div", tableColumn).each(function(i){
            this.innerHTML = column_vector[i];
            this.style.backgroundColor = null;
        });
    } else {
        $("div", tableColumn).each(function(){
            this.innerHTML = "x";
            this.style.backgroundColor = "mistyrose";
        });
    }
}

function updateRowVector(position){
    let row_vector = position_to_row_vector(board.position());
    //check feasibility
    let feasible = true;
    for (let i = 0; i < 8; i++){
        if (row_vector[i] === "z"){
            feasible = false;
            break;
        }
    }

    if (feasible){
        $("div", tableRow).each(function(i){
            this.innerHTML = row_vector[i];
            this.style.backgroundColor = null;
        });
    } else {
        $("div", tableRow).each(function(){
            this.innerHTML = "x";
            this.style.backgroundColor = "mistyrose";
        });
    }
}

function updatePermutationVector(){
    let permutation_vector = position_to_column_vector(board.position());

    //check feasibility
    let feasible = true;
    for (let i = 0; i < 8; i++){
        if (permutation_vector[i] === -1){
            feasible = false;
            break;
        }
        for (let j = i+1; j < 8; j++)
        {
            if (permutation_vector[i] === permutation_vector[j]){
                feasible = false;
                break;
            }
        }
    }

    if (feasible){
        $("div", tablePermutation).each(function(i){
            this.innerHTML = permutation_vector[i];
            this.style.backgroundColor = null;
        });
    } else {
        $("div", tablePermutation).each(function(x){
            this.innerHTML = "x";
            this.style.backgroundColor = "mistyrose";
        });
    }
}



function onSnapback(a, b, newPos, d){
    //highlightCollisions($board, newPos);
}

/**
 *
 * @param tableData
 * @param tableContainer
 * @returns {HTMLTableElement}
 */
function createMatrix(tableData, tableContainer) {
    var matrix = document.createElement('table');
    var tableBody = document.createElement('tbody');

    let i = 0;
    tableData.forEach(function(rowData) {
        rowData.forEach(function(cellData) {
            var cell = document.createElement('div');
            cell.appendChild(document.createTextNode(cellData));
            cell.setAttribute("childIndex", i);
            tableBody.appendChild(cell);
            i = i+1;
        });

        //tableBody.appendChild(row);
    });

    matrix.appendChild(tableBody);
    $(tableContainer)[0].appendChild(matrix);
    return matrix;
}

