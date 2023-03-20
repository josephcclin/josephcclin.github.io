import {
    position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, highlightCollisions
} from "./chessboard_utils.js";

let boards = initializeSolutions([
    ["board-solution-1", "#vec-solution-1"],
    ["board-solution-2", "#vec-solution-2"],
    ["board-solution-3", "#vec-solution-3"],
    ["board-solution-4", "#vec-solution-4"],
    ["board-solution-5", "#vec-solution-5"],
    ["board-solution-6", "#vec-solution-6"],
    ["board-solution-7", "#vec-solution-7"],
    ["board-solution-8", "#vec-solution-8"],
    ["board-solution-9", "#vec-solution-9"],
    ["board-solution-10", "#vec-solution-10"],
    ["board-solution-11", "#vec-solution-11"],
    ["board-solution-12", "#vec-solution-12"],
], [[4,2,0,5,7,1,3,6], [4,0,3,5,7,1,6,2], [6, 3, 1, 4, 7, 0, 2, 5],
    [5,3,0,4,7,1,6,2], [4,1,3,5,7,2,0,6], [2,0,6, 4, 7, 1,3,5],
    [2,0,6,4,7,1,3,5], [0,6,3,5,7,1,4,2], [0,6,4,7,1,3,5,2],
    [5,0,4,1,7,2,6,3], [2,5,1,4,7,0,6,3], [5,3,6,0,7,1,4,2]]);


function initializeSolutions(boardContainers, solutions){
    let boards = [];
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i][0];
        let vectorContainer = boardContainers[i][1];
        let solution = solutions[i];
        //console.log(column_vector_to_position(solution))

        //console.log(boardContainer);
        let board = Chessboard(boardContainer, {
            draggable: false,
            position: column_vector_to_position(solution),
            showNotation: false,
        });
        if (board === null)
            console.log(boardContainer);
        let table = createVector(position_to_column_vector(board.position()), vectorContainer);
        boards[i] = board;

        highlightCollisions($("#" + boardContainer), board.position());

    }
    return boards;
}





