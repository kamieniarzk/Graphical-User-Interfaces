using Calendar.Models;
using System;
using System.Collections.Generic;
namespace Calendar.ViewModels
{

    public class EventViewModel
    {
        public List<Event> GetAll()
        {
            return EventData.ReadDataFile();
        }

        public List<Event> GetDay(DateTime date)
        {
            List<Event> events = EventData.ReadDataFile();
            if (date != null)
            {
                events.RemoveAll(ev => ev.Date.ToString("yyyy-MM-dd") != date.ToString("yyyy-MM-dd"));
            }

            return events;
        }


        public void Add(Event e)
        {
            EventData.Add(e);
        }

        public Event Get(string id)
        {
            return EventData.Get(id);
        }

        public bool Edit(string id, DateTime dt, string description)
        {
            return EventData.Edit(id, dt, description);
        }

        public bool Remove(string id)
        {
            return EventData.Remove(id);
        }

    }
}