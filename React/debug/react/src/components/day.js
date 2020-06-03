import axios from "axios";
import { withRouter } from "react-router-dom";
import React, { useState, useEffect } from "react";
import moment from "moment";

function Day(props) {
  const [events, setEvents] = useState([]);
  const date = moment(props.match.params.date).format("YYYY-MM-DD");

  const getEvents = () => {
    axios
      .get(`/api/events/${date}`)
      .then((data) => data.data.data)
      .then((data) => JSON.parse(data))
      .then((data) => {
        const evs = data.map((ev) => {
          return {
            id: ev.Id,
            description: ev.Description,
            date: moment(ev.Date),
          };
        });
        setEvents(evs);
      })
      .catch((err) => {
        alert(err);
      });
  };

  const deleteEvent = (id) => {
    axios
      .delete(`/api/delete/${id}`)
      .then(() => {
        getEvents();
      })
      .catch((err) => console.error(err));
  };

  // Getting events as component mounts
  useEffect(() => {
    getEvents();
  }, []);

  var renderedEvents = [];
  var header = [];
  if (events.length > 0) {
    renderedEvents = events.map(
      (el, i) => (
        <tr key={i}>
          <td>{el.date.format("HH:mm")}</td>
          <td key={i * 3}>{el.description}</td>
          <td>
            <button
              className="right-icon button-blue"
              onClick={() => props.history.push(`/event/edit/${el.id}`)}
            >
              Edit
            </button>
          </td>
          <td>
            <button className="button-red" onClick={() => deleteEvent(el.id)}>
              Delete
            </button>
          </td>
        </tr>
      ),
      (header = (
        <tr className="events-header">
          <td>Time</td>
          <td>Description</td>
        </tr>
      ))
    );
  } else
    header = (
      <tr>
        <td className="events-header">There are no events on that day!</td>
      </tr>
    );

  return (
    <div>
      <h1 className="day-header"> {date} </h1>

      <table className="events-day">
        <thead>{header}</thead>
        <tbody>{renderedEvents}</tbody>
      </table>
      <div className="buttons">
        <button
          className="button-green"
          onClick={() => props.history.push(`/event/add/${date}`)}
        >
          Add new
        </button>

        <button
          className="button-red"
          onClick={() => props.history.push(`/home/${date}`)}
        >
          Close
        </button>
      </div>
    </div>
  );
}

export default withRouter(Day);
