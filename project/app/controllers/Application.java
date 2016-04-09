package controllers;
import models.FastForm;

import play.*;
import play.data.DynamicForm;
import play.data.Form;
import play.mvc.*;

import views.html.*;
import views.html.defaultpages.badRequest;

public class Application extends Controller {

    public static Result index() {
        return ok(Template.render("yesLogin","yesLogo","Index"));
    }
    public static Result cautari() {
        return ok(Template.render("yesLogin","yesLogo","Cautari"));
    }
    public static Result submitFastForm() {
        DynamicForm fastForm = Form.form().bindFromRequest();
        
        String sb="Tu vrei sa mergi de la "+fastForm.get("from")+" spre "+ fastForm.get("to");
        sb+=" la ora "+fastForm.get("leaveTime") + " cu escala la "+fastForm.get("detour");
        
        int validateRes = FastForm.validate(fastForm);
        
        if(validateRes==1)
            return ok(BadRequest.render("Formular validat!",sb.toString()));
        else
            return ok(BadRequest.render("Bad Request", "Argumente invalide! Te rog reincearca!"));
    }

    public static Result inregistrare() {
        return ok(Template.render("yesLogin","yesLogo","Inregistrare"));
    }

}