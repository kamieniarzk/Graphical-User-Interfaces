using Calendar.Models;
using Calendar.ViewModels;
using System;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Text.Json;

namespace Calendar.Controllers
{
    public class ApiController : Controller
    {


        [HttpGet]
        public JsonResult Events()
        {

            DateTime? date = DateTime.Parse((string)this.RouteData.Values["id"]);
            EventViewModel model = new EventViewModel();
            List<Event> eventsList = model.GetDay(date.Value);
            String data = JsonSerializer.Serialize(eventsList);
            return new JsonResult(new
            {
                status = "success",
                data = data
            });

        }

        [HttpGet]
        public JsonResult All()
        {

            EventViewModel model = new EventViewModel();
            List<Event> eventsList = model.GetAll();
            String data = JsonSerializer.Serialize(eventsList);
            return new JsonResult(new
            {
                status = "success",
                data = data
            });

        }

        [HttpGet]
        public JsonResult Event()
        {
            string id = (string)this.RouteData.Values["id"];
            EventViewModel model = new EventViewModel();
            Event ev = model.Get(id);
            String data = JsonSerializer.Serialize(ev);
            return new JsonResult(new
            {
                status = "success",
                data = data
            });

        }

        [HttpPost]
        public JsonResult Add(string date, string description)
        {
            EventViewModel model = new EventViewModel();
            model.Add(new Models.Event() { Date = DateTime.Parse(date), Description = description });
            return new JsonResult(new
            { });

        }

        [HttpPost]
        public JsonResult Edit(string date, string description, string id)
        {
            EventViewModel model = new EventViewModel();
            DateTime dat = DateTime.Parse(date);
            Console.WriteLine(date);
            if (model.Edit(id, dat, description))
                return new JsonResult(new
                { });
            else
                return new JsonResult(new
                {
                    status = "fail",
                    message = "Error while editing event"
                });
        }


        [HttpDelete]
        public JsonResult Delete()
        {
            String id = (string)this.RouteData.Values["id"];

            EventViewModel model = new EventViewModel();
            if (model.Remove(id))
            {
                return new JsonResult(new
                { });
            }
            else
            {
                return new JsonResult(new
                {
                    status = "fail",
                    message = "There is no event with that id" + id
                });

            }

        }
    }
}