package models;

import play.data.DynamicForm;


public class FastForm {
    public static int validate(DynamicForm myForm){
        
        if(myForm.get("from").isEmpty() || myForm.get("to").isEmpty() || myForm.get("leaveTime").isEmpty())
            return 0;
            
        return 1;
        
    }
    
}
