using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Calendar.Models
{
    public static class EventData
    { 
        public static List<Event> ReadDataFile()
        {
            List<Event> events = new List<Event>();
            string FilePath =@"./Models/data.txt";
            if (File.Exists(FilePath))
            {
                using (StreamReader stream = new StreamReader(FilePath))
                {
                    while (!stream.EndOfStream)
                    {
                        string line = stream.ReadLine();
                        string id = line.Substring(0, 32);
                        string dt = line.Substring(33, 19);
                        DateTime date = DateTime.Parse(dt);
                        string description = line.Substring(53, line.Length - (53)).Replace("@endl;", "\n");
                        Event newEvent = new Event() { Id = id, Date = date, Description = description };
                        events.Add(newEvent);               
                    }
                    Console.WriteLine();
                }
            }
            return events;
        }

        public static bool WriteDataFile(List<Event> Events)
        {
            string FilePath = @"./Models/data.txt";
            StreamWriter sw = null;
            if (File.Exists(FilePath))
                sw = new StreamWriter(FilePath);
            else
                sw = File.CreateText(FilePath);
            using (sw)
            {
                foreach (Event ev in Events)
                {
                    string description = "";
                    if (ev.Description != null)
                        description = ev.Description.Replace("\n", "@endl;");
                    sw.WriteLine(ev.Id + ' ' + ev.Date.ToString("yyyy'-'MM'-'dd'T'HH':'mm':'ss") + ' ' + description);
                }
            }
                return true;


        }

        private static string CreateId()
        {
            return Guid.NewGuid().ToString("N");
        }


        public static Event Get(string id)
        {
            List<Event> events = ReadDataFile();
            return events.Find(ev => (ev.Id == id));
        }

        public static void Add(Event added)
        {
            List<Event> events = ReadDataFile();
            added.Id = CreateId();
            events.Add(added);
            WriteDataFile(events);
        }

        public static bool Edit(string Id, DateTime dt, string description)
        {
            List<Event> events = ReadDataFile();
            int index = events.FindIndex(ev => (ev.Id == Id));
            if(index != -1)
            {
                events.ElementAt(index).Description = description;
                events.ElementAt(index).Date = dt;
                WriteDataFile(events);
                return true;
            }
            return false;            
        }

        public static bool Remove(string id)
        {
            List<Event> events = ReadDataFile();
            int index = events.FindIndex(ev => (ev.Id == id));
            if (index != -1)
            {
                events.RemoveAt(index);
                WriteDataFile(events);
                return true;
            }
            return false;
        }
    }
}
