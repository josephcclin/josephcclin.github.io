
import {position_to_column_vector, field_to_index, index_to_field, example_positions, column_vector_to_position,
    random_vector, createVector, index_to_col_name, shuffle} from "./chessboard_utils.js";

let boards = initializeBoards([
    ["board-inversion-mutation-1", "#inversion-mutation-parent"],
    ["board-inversion-mutation-2", "#inversion-mutation-child"],
    ["board-shuffle-mutation-1", "#shuffle-mutation-parent"],
    ["board-shuffle-mutation-2", "#shuffle-mutation-child"],
]);

let divsParentInversion = $(boards[0].table).find("div");
let divsChildInversion = $(boards[1].table).find("div");

let divsParentShuffle = $(boards[2].table).find("div");
let divsChildShuffle = $(boards[3].table).find("div");

$( function() {
    $( "#slider-range-inversion" ).slider({
        range: true,
        min: 0,
        max: 8,
        values: [ 3, 5 ],
        slide: function( event, ui ) {
            if (ui.values[0] === ui.values[1])
                return false;
            updateVectorsInversion(ui.values, divsParentInversion, divsChildInversion, boards[0], boards[1]);
        }
    });
} );

$( function() {
    $( "#slider-range-shuffle" ).slider({
        range: true,
        min: 0,
        max: 8,
        values: [ 3, 5 ],
        slide: function( event, ui ) {
            if (ui.values[0] === ui.values[1])
                return false;
            //console.log(ui.values);
            updateVectorsShuffle(ui.values, divsParentShuffle, divsChildShuffle, boards[2], boards[3]);
        }
    });
} );

boards[1].position(boards[0].position())
boards[3].position(boards[2].position())

updateVectorsInversion([ 3, 5 ], divsParentInversion, divsChildInversion, boards[0], boards[1]);
updateVectorsShuffle([ 3, 5 ], divsParentShuffle, divsChildShuffle, boards[2], boards[3]);


function updateVectorsInversion(values, divsParent, divsChild, boardParent, boardChild){
    //retrieve the x first elements
    let newVectorChild = position_to_column_vector(boardChild.position());
    let newVector = position_to_column_vector(boardParent.position());

    for (let i = 0; i < 8; i++) {
        divsChild[i].innerHTML = divsParent[i].innerHTML;
        divsChild[i].style.backgroundColor = null;
    }

    for (let i = 0; i < 8; i++){

        if (i < values[0] || i >= values[1])
        {
            boardChild.move(index_to_col_name[i]+(newVectorChild[i]) + "-" + index_to_col_name[i]+(newVector[i]));
        }
        else
        {
            let j = i - values[0];
            boardChild.move(index_to_col_name[values[0]+j]+(newVectorChild[values[0]+j]) + "-" + index_to_col_name[values[0]+j]+(newVector[values[1]-(j+1)]));

            //newVector[values[0] + i] = shuffleValues[i];
            divsChild[i].innerHTML = newVector[values[1]-(j+1)];
            divsChild[i].style.backgroundColor = "mistyrose";
        }
    }

    //boardChild.position(column_vector_to_position(newVector));
}

function updateVectorsShuffle(values, divsParent, divsChild, boardParent, boardChild){
    //retrieve the x first elements
    let newVectorChild = position_to_column_vector(boardChild.position());
    let newVector = position_to_column_vector(boardParent.position());

    for (let i = 0; i < 8; i++) {
        //newVectorChild[i] = parseInt(divsChild[i].innerHTML);
        divsChild[i].innerHTML = divsParent[i].innerHTML;
        divsChild[i].style.backgroundColor = null;
    }

    let shuffleValues = newVector.slice(values[0], values[1]);
    shuffle(shuffleValues);

    let posTemp = boardChild.position();
    for (let i = 0; i < 8; i++){
        if (i < values[0] || i >= values[1])
        {
            boardChild.move(index_to_col_name[i]+(newVectorChild[i]) + "-" + index_to_col_name[i]+(newVector[i]));
        }
        else
        {
            let j = i - values[0];
            boardChild.move(index_to_col_name[values[0]+j]+(newVectorChild[values[0]+j]) + "-" + index_to_col_name[values[0]+j]+(shuffleValues[j]));

            //newVector[values[0] + i] = shuffleValues[i];
            divsChild[i].innerHTML = shuffleValues[j];
            divsChild[i].style.backgroundColor = "mistyrose";
        }
    }
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
        let table = createVector(position_to_column_vector(board.position()), vectorContainer);
        $("div", table).click(function(){ mutateQueen(this, board);});
        board.table = table;
        boards[i] = board;
    }
    return boards;
}





