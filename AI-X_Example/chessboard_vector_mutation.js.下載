import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, position_to_row_vector} from "./chessboard_utils.js";

initializeBoards([
    ["board-vector-mutation-1", "#vector-mutation-1"],
]);

function initializeBoards(boardContainers){
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
        let table = createVector(position_to_column_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen(this, board);});
    }
}

function mutateQueen(field, board){
    let row = field.innerHTML;
    let column = index_to_col_name[field.getAttribute("childindex")];
    let field_before = column + row;

    let new_row = 8- Math.floor(Math.random() * 8);
    while (new_row === row){
        new_row = 8- Math.floor(Math.random() * 8);
    }
    let field_after = column + new_row;

    let position = board.position();

    delete position[field_before]; // update board
    position[field_after] = "bQ";
    field.innerHTML = new_row; // update matrix
    board.position(position);
}



let boards2 = initializeBoards2([
    ["board-vector-mutation-2", "#vector-mutation-2", example_positions[0]],
]);



function initializeBoards2(boardContainers){
    let boards = [];
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i][0];
        let vectorContainer = boardContainers[i][1];
        let position = boardContainers[i][2];
        let board = Chessboard(boardContainer, {
            draggable: false,
            position: position,
            showNotation: false,
            onDrop: onDrop,
            boardIndex: i,
            boardContainer: boardContainer,
            tableContainer: vectorContainer
        });
        boards[i] = board;
        let table = createVector(position_to_row_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen2(this, board);});
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


function mutateQueen2(field, board){
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






