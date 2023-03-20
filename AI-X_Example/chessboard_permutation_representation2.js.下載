import {position_to_column_vector, field_to_index, index_to_field, example_positions, createVector} from "./chessboard_utils.js";
import {index_to_col_name} from "./chessboard_utils.js";
import {col_name_to_index} from "./chessboard_utils.js";

initializeBoards([
    ["board-permutation-example-4", "#board-permutation-4", example_positions[0]],
]);

function initializeBoards(boardContainers){
    for (let i in boardContainers) {
        let boardContainer = boardContainers[i][0];
        let vectorContainer = boardContainers[i][1];
        let position = boardContainers[i][2];
        //console.log(boardContainer);
        let board = Chessboard(boardContainer, {
            draggable: false,
            position: position,
            showNotation: false,
        });
        board.selected = null;

        let table = createVector(position_to_column_vector(board.position()), vectorContainer);

        let pieces = $("#" + boardContainer).find("div");
        pieces.click(function(){ selectQueen(this, board, table, pieces);});

        $("div", table).click(function(){ selectCell(this, board, pieces);});
    }
}

function selectQueen(field, board, table, pieces){
    if (field.getAttribute("data-square") in board.position()) {
        let tablecell = $("div", table)[col_name_to_index[field.getAttribute("data-square")[0]]];
        selectCell(tablecell, board, pieces);
    }
}

function selectCell(field, board, pieces){
    let row = field.innerHTML;
    let column = index_to_col_name[field.getAttribute("childindex")];
    //console.log("select Cell:", column+row);

    if (board.selected === null)
    {

        //select element
        board.selected = column + row;
        board.selectedField = field;
        $(field).toggleClass("selected");

        for (let i = 0; i < 64; i++){
            if (pieces[i].getAttribute("data-square") === board.selected){
                pieces[i].classList.add("highlight-yellow");
                return;
            }
        }

    } else {
        //do swap between elements
        let a1 = board.selected;
        let a2 = column + row;
        let b1 = a1[0] + a2[1];
        let b2 = a2[0] + a1[1];

        for (let i = 0; i < 64; i++){
            if (pieces[i].getAttribute("data-square") === board.selected){
                pieces[i].classList.remove("highlight-yellow");
            }
        }

        // move first queen
        let pos = board.position();
        delete pos[a1];
        pos[b1] = "bQ";
        board.position(pos);
        pos = board.position();

        // move second queen
        delete pos[a2];
        pos[b2] = "bQ";
        board.position(pos);
        field.innerHTML = b2[1];
        board.selectedField.innerHTML = b1[1];
        $(board.selectedField).toggleClass("selected");

        board.selected = null;
        board.selectedField = null;
    }
}








