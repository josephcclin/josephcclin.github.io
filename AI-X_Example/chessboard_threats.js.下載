import {
    highlightCollisions, highlightPosition
} from "./chessboard_utils.js";

let boards = initializeSolutions(["board-horizontal-threat",
    "board-vertical-threat",
    "board-diagonal-threat"
], [{"b5": "bQ", "f5": "bQ"},
    {"d2": "bQ", "d8": "bQ"},
    {"b3": "bQ", "f7": "bQ"},
], [{"c5": "bQ", "d5": "bQ", "e5": "bQ"},
    {"d3": "bQ", "d4": "bQ", "d5": "bQ", "d6": "bQ", "d7": "bQ"},
    {"c4": "bQ", "d5": "bQ", "e6": "bQ"}]);


function initializeSolutions(boardContainers, solutions, threats){
    let boards = [];
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i];
        let solution = solutions[i];
        let threat = threats[i];

        //console.log(boardContainer);
        let board = Chessboard(boardContainer, {
            draggable: false,
            position: solution,
            showNotation: false,
        });
        if (board === null)
            console.log(boardContainer);
        boards[i] = board;

        highlightCollisions($("#" + boardContainer), board.position());
        highlightPosition($("#" + boardContainer), threat)
    }
    return boards;
}





