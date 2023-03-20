import {position_to_row_vector, index_to_col_name, field_to_index, index_to_field, example_positions, createVector} from "./chessboard_utils.js";
import {highlightCollisions} from "./chessboard_utils.js";

let boards = initializeBoards([
    ["board-row-vector-example-1", "#board-row-vector-1", example_positions[0]],
    ["board-row-vector-example-2", "#board-row-vector-2", example_positions[3]],
    ["board-row-vector-example-3", "#board-row-vector-3", example_positions[2]]
]);



function initializeBoards(boardContainers){
    let boards = [];
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i][0];
        let vectorContainer = boardContainers[i][1];
        let position = boardContainers[i][2];
        let board = Chessboard(boardContainer, {
            draggable: true,
            position: position,
            showNotation: false,
            onDrop: onDrop,
            boardIndex: i,
            boardContainer: boardContainer,
            tableContainer: vectorContainer
        });
        boards[i] = board;
        let table = createVector(position_to_row_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen(this, board);});
    }
    return boards;
}

function onDrop(source, target, piece, newPos, oldPos, orientation){
    if (target in oldPos || target === "offboard" || target[1] !== source[1]){
        return 'snapback';
    }

    const divIndex = 8-target[1];
    const targetColumn = target[0];
    const position = newPos;
    let board = boards[this.boardIndex];

    delete position[source];
    position[target] = "bQ";
    $("div", this.tableContainer)[divIndex].innerHTML = targetColumn;

    board.position(position);
    //highlightCollisions($(this.boardContainer), board.position())
}


function mutateQueen(field, board){
    let column = field.innerHTML;
    let row = 8 - field.getAttribute("childindex");
    let field_before = column + row;

    let new_column =  index_to_col_name[Math.floor(Math.random() * 8)];
    while (new_column === column){
        new_column =  index_to_col_name[Math.floor(Math.random() * 8)];
    }
    let field_after = new_column + row;

    let position = board.position();

    delete position[field_before]; // update board
    position[field_after] = "bQ";
    field.innerHTML = new_column; // update matrix
    board.position(position);
}
