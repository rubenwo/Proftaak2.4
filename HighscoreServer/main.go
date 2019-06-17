package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"

	"github.com/gorilla/mux"
)

//Highscore is a struct for marshalling highscore data to and from json
type Highscore struct {
	Score  string `json:"score"`
	Player string `json:"player"`
}

func main() {
	router := mux.NewRouter()

	router.HandleFunc("/highscore/{player}/{score}", postHighscore).Methods("GET")
	router.HandleFunc("/highscore/{player}", getHighscore).Methods("GET")

	log.Fatal(http.ListenAndServe(":80", router))
}

func postHighscore(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	player := vars["player"]
	score := vars["score"]
	fmt.Println("Got a postHighscore request for player:", player, "with score:", score)
	data, err := ioutil.ReadFile(player + ".json")

	var hs Highscore
	err = json.Unmarshal(data, &hs)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	if hs.Score > score {
		w.Write([]byte(hs.Score))
	} else {
		data, err = json.Marshal(Highscore{
			Score:  score,
			Player: player,
		})
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		err = ioutil.WriteFile(player+".json", data, 0644)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		w.Write([]byte(score))
	}
}

func getHighscore(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	player := vars["player"]
	fmt.Println("Got a getHighscore Request for player:", player)
	data, err := ioutil.ReadFile(player + ".json")
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}
	var hs Highscore
	err = json.Unmarshal(data, &hs)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	w.Write([]byte(hs.Score))
}
