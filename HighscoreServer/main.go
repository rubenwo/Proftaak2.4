package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

var scores map[string]string

func main() {
	router := mux.NewRouter()
	scores = make(map[string]string)
	loadScores()
	router.HandleFunc("/highscore/{player}/{score}", postHighscore).Methods("GET")
	router.HandleFunc("/highscore/{player}", getHighscore).Methods("GET")

	log.Fatal(http.ListenAndServe(":80", router))
}

func postHighscore(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	player := vars["player"]
	score := vars["score"]

	fmt.Println("Got a postHighscore request for player:", player, "with score:", score)
	if scores[player] < score {
		scores[player] = score
	}
	w.Write([]byte(scores[player]))
	saveScores()
}

func getHighscore(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	player := vars["player"]
	fmt.Println("Got a getHighscore Request for player:", player)
	if _, ok := scores[player]; ok {
		//do something here
		w.Write([]byte(scores[player]))
	} else {
		w.Write([]byte("0"))
	}
}

func saveScores() {
	data, err := json.Marshal(scores)
	if err != nil {
		fmt.Println(err)
	}
	err = ioutil.WriteFile("scores.json", data, 0644)
	if err != nil {
		fmt.Println(err)
	}
}

func loadScores() {
	data, err := ioutil.ReadFile("scores.json")
	if err != nil {
		fmt.Println(err)
	}
	err = json.Unmarshal(data, &scores)
	if err != nil {
		fmt.Println(err)
	}
}
