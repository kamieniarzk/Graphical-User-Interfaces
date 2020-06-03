import React from "react";
import Calendar from "./components/calendar";
import Day from "./components/day";
import Event from "./components/event";
import { BrowserRouter as Router, Switch, Route } from "react-router-dom";
import axios from "axios";

axios.defaults.baseURL = "http://localhost:5000/";

function App() {
  return (
    <Router>
      <div className="App">
        <Switch>
          <Route path="/event/add/:date" component={Event} />
          <Route path="/event/edit/:id" component={Event} />
          <Route path="/day/:date" component={Day} />
          <Route path="/home/:date" component={Calendar} />
          <Route path="/" exact component={Calendar} />
        </Switch>
      </div>
    </Router>
  );
}

export default App;
