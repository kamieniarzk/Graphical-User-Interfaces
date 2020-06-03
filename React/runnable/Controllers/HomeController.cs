using Calendar.Models;
using Calendar.ViewModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System.Collections.Generic;
using System;
using System.Diagnostics;
using System.Text.Json;

namespace Calendar.Controllers
{
    public class HomeController : Controller
    {
        public static DateTime CurrentDate = DateTime.Now;
        private readonly ILogger<HomeController> _logger;
         [HttpGet]
        public JsonResult GetEvents()
        {
           
            EventViewModel eventsModel = new EventViewModel();
            List<Event> events = eventsModel.GetAll();
            String result = JsonSerializer.Serialize(events);

            return new JsonResult(new
            {
                status = "success",
                data = result
            });
        }
        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            EventViewModel events = new EventViewModel();
            ViewBag.date = CurrentDate.ToString("yyyy-MM-dd");
            return View(events);
        }

        public IActionResult Day(string date)
        {
            DateTime dt = DateTime.Parse(date);
            CurrentDate = dt;
            ViewBag.date = dt;
            EventViewModel events = new EventViewModel();
            return View(events);
        }


        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
