import {squareClass, position_to_binary_board, field_to_index, index_to_field, example_positions, createMatrix} from "./chessboard_utils.js";

// setup board
let board = Chessboard('board-for-matrix-representation', {
    draggable: false,
    position: example_positions[0],
});
let $board = $('#board-for-matrix-representation');

// add on click event to toggle queens on a field
$board.find('.' + squareClass).click(function(){ toggleQueenOnBoard(board, this, "#board-matrix-representation"); });

// create matrix representation
let matrix = createMatrix(position_to_binary_board(board.position())[0], "#board-matrix-representation");
$("div", matrix).click(function(){ toggleQueenOnMatrix(this, board);});
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
function toggleQueenOnBoard(board, chessfield, linkedmatrix){
    const field = chessfield.getAttribute("data-square");
    const position = board.position();
    let divIndex = field_to_index(field);

    if (field in position)
    {
        delete position[field]; // update board
        $(linkedmatrix).find("div")[divIndex].innerHTML = 0; // update matrix
    }
    else
    {
        position[field] = "bQ"; // update board
        $(linkedmatrix).find("div")[divIndex].innerHTML = 1; // update matrix
    }
    board.position(position);
    updateStyle();

}

/**
 *
 * @param diffield
 * @param board
 */
function toggleQueenOnMatrix(diffield, board) {
    const index = diffield.getAttribute("childindex");
    const position = board.position();
    let field = index_to_field(index);

    if (field in position)
    {
        delete position[field]; // update board
        diffield.innerHTML = 0; // update matrix
    }
    else
    {
        position[field] = "bQ"; // update board
        diffield.innerHTML = 1; // update matrix
    }
    board.position(position);
    updateStyle();

}

