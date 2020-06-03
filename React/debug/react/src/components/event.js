import axios from "axios";
import { withRouter } from "react-router-dom";
import React, { useState, useEffect } from "react";
import moment from "moment";

function Event(props) {
  const [date, setDate] = useState(
    moment(props.match.params.date).format("YYYY-MM-DD")
  );
  const id = props.match.params.id;
  const [description, setDescription] = useState("");
  const [time, setTime] = useState("");

  const handleSubmit = (event) => {
    event.preventDefault();
    if (id != null) return edit(event);
    return add(event);
  };
  const getEvent = () => {
    axios
      .get(`/api/event/${id}`)
      .then((data) => data.data.data)
      .then((data) => JSON.parse(data))
      .then((data) => {
        setDescription(data.Description);
        setTime(moment(data.Date).format("hh:mm"));
        setDate(
          moment(data.Date.slice(0, 10), "YYYY-MM-DD").format("YYYY-MM-DD")
        );
        console.log(
          "slice = " + moment(data.Date.slice(0, 10)).format("YYYY-MM-DD")
        );
      })
      .catch((err) => {
        alert(err);
      });
  };

  useEffect(() => {
    if (id != null) getEvent();
  }, []);

  const add = (event) => {
    event.preventDefault();
    let data = getData();
    console.log(data.date);
    axios
      .post(`/api/add/`, data, {
        headers: {
          "Content-Type": "multipart/form-data",
        },
      })
      .then((data) => {
        props.history.push(`/day/${date}`);
      })
      .catch((err) => {
        alert(`error occured`);
        props.history.push("/home");
      });
  };

  const edit = (event) => {
    event.preventDefault();
    let data = getData();
    console.log(data.date);
    axios
      .post(`/api/edit/`, data, {
        headers: {
          "Content-Type": "multipart/form-data",
        },
      })
      .then((data) => {
        props.history.push(`/day/${date}`);
      })
      .catch((err) => {
        alert(`error occured`);
        props.history.push("/home");
      });
  };

  const setT = (event) => {
    setTime(event.target.value);
  };
  const setDsc = (event) => {
    setDescription(event.target.value);
  };

  const getData = () => {
    let data = new FormData();
    data.set("date", moment(date + " " + time).format("YYYY-MM-DDThh:mm"));
    data.set("description", description);
    data.set("id", id);
    return data;
  };

  return (
    <div className="event-edit">
      <form onSubmit={handleSubmit}>
        <label className="input-label">Description:</label>
        <input
          type="text"
          name="description"
          onChange={setDsc}
          value={description}
        />
        <label className="input-label">Time:</label>
        <input type="time" name="time" onChange={setT} value={time} />
        <div className="buttons">
          <button className="button-green" type="submit">
            Submit
          </button>
          <button
            className="button-red"
            type="button"
            onClick={() => props.history.push(`/day/${date}`)}
          >
            Close
          </button>
        </div>
      </form>
    </div>
  );
}

export default withRouter(Event);
