import {highlightCollisions, example_positions} from "./chessboard_utils.js";

let board = Chessboard('board-letsplay', {
    draggable: true,
    position: example_positions[0],
    onDrop: onDrop,
    onSnapbackEnd: onSnapback
});

let $board = $('#board-letsplay');
highlightCollisions($board, board.position());

function onDrop (source, target, piece, newPos, oldPos, orientation) {
    // block putting two queens on the same field
    if (target in oldPos){
        return 'snapback';
    }

    // update highlighting of safe positions
    highlightCollisions($board, newPos);
}

function onSnapback(a, b, position, d){
    highlightCollisions($board, position);

}