import React, { useState, useEffect } from "react";
import moment from "moment"; // just for convenience with time handling
import { withRouter } from "react-router-dom";
import axios from "axios";
import "./style.css";

const Calendar = (props) => {
  const date = props.match.params.date ? moment(props.match.params.date) : null;
  const [current, setCurrent] = useState(date || moment());
  const [today] = useState(moment());
  const [events, setEvents] = useState([]);

  useEffect(() => {
    getEvents();
  }, []);

  const getEvents = () => {
    axios
      .get(`/api/all/`)
      .then((res) => res.data.data)
      .then((data) => JSON.parse(data))
      .then((data) => {
        const events = data.map((el) => moment(el.Date));
        setEvents(events);
      })
      .catch((err) => {
        alert(err);
      });
  };

  const year = () => {
    return current.format("Y");
  };

  const month = () => {
    return current.format("MMMM");
  };

  const daysInMonth = () => {
    return current.daysInMonth();
  };

  const currentDay = () => {
    return parseInt(today.format("D"));
  };

  const firstDayIndex = () => {
    return moment(current).startOf("month").format("d"); // returns the index of first day of the month (0 - Sun, 1 - Mon ... 6 - Sat)
  };

  const nextMonth = () => {
    let currentDate = moment(current).add(1, "month");
    setCurrent(currentDate);
  };

  const prevMonth = () => {
    let currentDate = moment(current).subtract(1, "month");
    setCurrent(currentDate);
  };

  const onDayClick = (e, date) => {
    props.history.push(`/day/${date}`);
  };

  let dayNames = moment.weekdaysShort().map((day) => {
    return (
      <td key={day} className="week-day">
        {day}
      </td>
    );
  });

  let emptyDays = []; // number of empty cells in the calendar table before the 1st day of the month
  for (let i = 0; i < firstDayIndex(); i++) {
    emptyDays.push(
      // to prevent key duplicates i * 100
      <td key={i * 87} className="day-empty">
        {""}
      </td>
    );
  }

  let days = []; // table cells with the actual days (numbers)
  for (let i = 1; i <= daysInMonth(); i++) {
    let style =
      i === currentDay() && current.month() === today.month()
        ? "day-current" // checking if given day is the current date
        : "day";
    const day = moment(current);
    day.set("date", i);
    if (
      events.find((el) => el.format("DD-MM-YYYY") === day.format("DD-MM-YYYY"))
    ) {
      style += " day-event"; // styling the days with events
    }
    let date = moment([
      parseInt(current.year()),
      parseInt(current.month()),
      i,
    ]).format("YYYY-MM-DD");
    days.push(
      <td
        key={i}
        className={style}
        onClick={(e) => {
          onDayClick(e, date);
        }}
      >
        <span>{i}</span>
      </td>
    );
  }

  var tableData = [...emptyDays, ...days];
  let dayRows = [];
  let tableCells = [];

  // slicing all the data into rows of 7
  tableData.forEach((row, i) => {
    if (i % 7 !== 0) {
      tableCells.push(row);
    } else {
      let tempRow = tableCells.slice();
      dayRows.push(tempRow);
      tableCells = [];
      tableCells.push(row);
    }
    if (i === tableData.length - 1) {
      let insertRow = tableCells.slice();
      dayRows.push(insertRow);
    }
  });

  let tableRows = dayRows.map((d, i) => {
    return <tr key={i * 100}>{d}</tr>; // to prevent key duplicates i * 100
  });

  return (
    <div className="calendar">
      <table className="calendar-table">
        <thead>
          <tr className="calendar-header">
            <td colSpan="1" className="nav-month">
              <i
                className="arrow prev fa fa-fw fa-chevron-left"
                onClick={(e) => {
                  prevMonth();
                }}
              ></i>
            </td>
            <td colSpan="5" className="month-label">
              {month() + " " + year()}
            </td>
            <td className="nav-month">
              <i
                className="arrow prev fa fa-fw fa-chevron-right right-icon"
                onClick={(e) => {
                  nextMonth();
                }}
              ></i>
            </td>
          </tr>
        </thead>
        <tbody>
          <tr>{dayNames}</tr>
          {tableRows}
        </tbody>
      </table>
    </div>
  );
};

export default withRouter(Calendar);
