<?php

class Calendar {
        //calendar_tempalate
        public $cal_tmp;
        //calendar_stylesheet
        public     $cal_ssht;
        //calendar_stylesheet_prefix
        public $cal_ssht_pfx;

        //calendar_show_date
        public $cal_s_date;

        //calendar_language
        public $cal_lang='eng';

        //calendar_link_to_add
        public $cal_lnk_add;
        //calendar_link_concat_string
        public $cal_lnk_cstr;
        //calendar_link_variable_prefix
        public $cal_lnk_vprfx;
        //calendar_total_height
        public $cal_t_ht;
        //calendar_total_width
        public $cal_t_wt;

        //calendar_work_tempalate
        public $cal_wrk_tmp;

        //Calendar time issues
        public $cal_time_hour_diff;
        
        function set_calendar_tempalate($value){
                return $this->cal_tmp = $this->get_file($value);} 
        function set_calendar_stylesheet($value){
                return $this->cal_ssht = $value;} 
        function set_calendar_stylesheet_prefix($value){
                return $this->cal_ssht_pfx = $value;} 
        //Time
        function set_calendar_hour_difference($value){
                return $this->cal_time_hour_diff = $value;} 
        
        function set_calendar_show_date($value){
                return $this->cal_s_date = $value;} 

        /* By Dirk Olten ( mail@extrabyte.de ) */
        function set_calendar_language($value){
                return $this->cal_lang = $value;} 

        function set_calendar_link_to_add($value){
                return $this->cal_lnk_add = $value;} 
        function set_calendar_link_concat_string($value){
                return $this->cal_lnk_cstr = $value;} 
        function set_calendar_link_variable_prefix($value){
                return $this->cal_lnk_vprfx = $value;} 
        
        function set_calendar_total_height($value){
                return $this->cal_t_ht = $value;} 
        function set_calendar_total_width($value){
                return $this->cal_t_wt = $value;} 

        //Initialize the constructor of the class with calendar date , tempalte html with smart tags, stylesheet and prefix to add for stylesheet.
        function Calendar($date,$tempalate,$stylesheet,$stylesheet_prefix){
                $this->cal_s_date = $this->set_calendar_show_date($date);
                $this->calendar_calendar_stylesheet = $this->set_calendar_stylesheet($stylesheet);
                $this->cal_ssht_pfx = $this->set_calendar_stylesheet_prefix($stylesheet_prefix);
                $this->calendar_calendar_tempalate = $this->set_calendar_tempalate($tempalate);
        }

        function showmonth(){
                $this->cal_wrk_tmp = $this->exrt_nd_temp_frm_mtemp ('<!-- BEGIN Calendar_Month_Type -->','<!-- END Calendar_Month_Type -->');
                $this->rp_cal_wrk_tmp('{C_STYLESHEET_C}',$this->cal_ssht,'','1');
                // This feature was added to the class by Mr.Matthew Waygood Email: matthew@waygoodstuff.co.uk
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_TODAY_BUTTON_C}',$this->cal_ssht_pfx.'-cal-today','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_BOX_C}',$this->cal_ssht_pfx.'-cal-box','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_BACK_C}',$this->cal_ssht_pfx.'-cal-back','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_YEAR_BOX_C}',$this->cal_ssht_pfx.'-cal-year-box','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_YEAR_PREVIOUS_BUTTON_C}',$this->cal_ssht_pfx.'-cal-year-prev','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALEDNDE_YEAR_TEXT_C}',$this->cal_ssht_pfx.'-cal-year','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_YEAR_NEXT_BUTTON_C}',$this->cal_ssht_pfx.'-cal-year-next','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_MONTH_BOX_C}',$this->cal_ssht_pfx.'-cal-month-box','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_MONTH_PREVIOUS_BUTTON_C}',$this->cal_ssht_pfx.'-cal-month-prev','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_MONTH_TEXT_C}',$this->cal_ssht_pfx.'-cal-month','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_MONTH_NEXT_BUTTON_C}',$this->cal_ssht_pfx.'-cal-month-next','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_CALENDAR_DAYS_OF_WEEK_BOX_C}',$this->cal_ssht_pfx.'-cal-days-box','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_DAYS_OF_WEEK_START_C}',$this->cal_ssht_pfx.'-cal-day-start','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_DAYS_OF_WEEK_REST_C}',$this->cal_ssht_pfx.'-cal-day-rest','','1');
                
                $this->rp_cal_wrk_tmp('{C_CSS_WEEK_NO_C}',$this->cal_ssht_pfx.'-cal-week-no-head','','1');
                $this->rp_cal_wrk_tmp('{C_CSS_WEEK_NO_X_C}',$this->cal_ssht_pfx.'-cal-week-no-rest','','1');

                $this->rp_cal_wrk_tmp('{C_CAL_HEIGHT_C}',(string)$this->cal_t_ht,'','1');
                $this->rp_cal_wrk_tmp('{C_CAL_WIDTH_C}',(string)$this->cal_t_wt,'','1');
                $temp_calendar_row_height = (string)(round($this->cal_t_ht / 9));
                $this->rp_cal_wrk_tmp('{C_CAL_ROW_HEIGHT_C}',$temp_calendar_row_height,'','1');

                // Generate For Today 
                // This feature was added to the class by Mr.Matthew Waygood ( mwwaygoo@hotmail.com )
                $this->rp_cal_wrk_tmp('{C_TODAY_C}','Go Today',$this->gen_cal_lnk($this->get_today_date()),'1');

                // Generate For Year 
                $this->rp_cal_wrk_tmp('{C_YEAR_PREV_C}','<<',$this->gen_cal_lnk($this->get_yr_prev($this->cal_s_date)),'1');
                $this->rp_cal_wrk_tmp('{C_YEAR_C}',$this->get_year($this->cal_s_date,'1'),'','1');
                $this->rp_cal_wrk_tmp('{C_YEAR_NEXT_C}','>>',$this->gen_cal_lnk($this->get_yr_nxt($this->cal_s_date)),'1');
                
                //Generate for Month
                $this->rp_cal_wrk_tmp('{C_MONTH_PREV_C}','<<',$this->gen_cal_lnk($this->get_mnt_prev($this->cal_s_date)),'1');
                $this->rp_cal_wrk_tmp('{C_MONTH_C}',$this->get_month($this->cal_s_date,'1'),'','1');
                $this->rp_cal_wrk_tmp('{C_MONTH_NEXT_C}','>>',$this->gen_cal_lnk($this->get_mnt_nxt($this->cal_s_date)),'1');
                
                //Generate Days
                //start day = location of the given month in 0 to 365 - start of the week of the month + 1
                $start_day= $this->get_mnt_strt_loc_in_yr($this->cal_s_date) - $this->get_mnt_strt_day($this->cal_s_date,'1') + 1 ;

                if($this->get_month($this->cal_s_date,'3')=='01')
                        $week_no=1;
                else
                        $week_no=$this->get_week_no('01-'.$this->get_month($this->cal_s_date,'3').'-'.$this->get_year($this->cal_s_date,'1'));

                for($current_row=1;$current_row<=6;$current_row++){
                        for($current_column=1;$current_column<=7;$current_column++){
                                $srch_week_str='{C_WEEK_NO_'.$current_row.'_C}';
                                $this->rp_cal_wrk_tmp($srch_week_str,(string)($week_no+($current_row-1)),'','1');
                                
                                $srch_str='{C_DAY_MATRIX_'.$current_row.'X'.$current_column.'_C}';
                                $srch_css_str='{C_CSS_DAY_MATRIX_'.$current_row.'X'.$current_column.'_C}';
                                $gen_date=$this->get_date_frm_loc_in_yr($start_day,$this->cal_s_date);
                                $rep_str=$this->get_day($gen_date,'1');
                                $start_day++;
                                if ($this->get_month($this->cal_s_date,'4')==$this->get_month($gen_date,'4')){
                                        $this->rp_cal_wrk_tmp($srch_str,$rep_str,$this->gen_cal_lnk($gen_date),'1');}
                                else{
                                        $this->rp_cal_wrk_tmp($srch_str,$rep_str,$this->gen_cal_lnk($gen_date),'2');}
                                if($this->get_today_date()==$gen_date){
                                        $this->rp_cal_wrk_tmp($srch_css_str,$this->cal_ssht_pfx.'-cal-cur-day','','1');}
                                elseif ($gen_date==$this->cal_s_date){
                                        $this->rp_cal_wrk_tmp($srch_css_str,$this->cal_ssht_pfx.'-cal-sel-day','','1');}
                                elseif ($current_column==1){
                                        $this->rp_cal_wrk_tmp($srch_css_str,$this->cal_ssht_pfx.'-cal-days-start','','1');}
                                else{
                                        $this->rp_cal_wrk_tmp($srch_css_str,$this->cal_ssht_pfx.'-cal-days-rest','','1');}
                }       }
                print $this->cal_wrk_tmp;
        }

        //extract_needed_tempalate_from_main_tempalate
        function exrt_nd_temp_frm_mtemp($start_from_tag,$end_to_tag){
                $strt_frm_tg_len=strlen($start_from_tag);
                $end_to_tg_len=strlen($end_to_tag);
                $strt_frm_tg_ocr_pos=strpos($this->cal_tmp,$start_from_tag);
                $end_to_tg_ocr_pos=strpos($this->cal_tmp,$end_to_tag);
                return substr($this->cal_tmp,$strt_frm_tg_ocr_pos+$strt_frm_tg_len,($end_to_tg_ocr_pos-$strt_frm_tg_ocr_pos)-($end_to_tg_len+2));
        }
        //get the file into a string
        function get_file($filename){
                if($fp = fopen($filename, 'rb')){
                        $return = fread($fp, filesize($filename));fclose($fp);return $return;}
                else{
                        return FALSE;}
        }
        //replace_calendar_work_template
        function rp_cal_wrk_tmp($find,$replace,$link,$type){
                global $ROOT_PATH,$WEB_ROOT,$HOME_PATH,$CATEGORY;
                $link = eregi_replace("^_date=",$WEB_ROOT.'/'.$HOME_PATH.'/AllNews/'.$CATEGORY,$link);
                $link = eregi_replace('([0-9]{2})-([0-9]{2})-([0-9]{4})','\3-\2-\1',$link);
                if($link!=''){
                        if ($type=='1'){
                                $replacestr='<a href="'.$link.'" class="'.$this->cal_ssht_pfx.'-cal-link'.'">'.$replace.'</a>';}
                        elseif ($type=='2'){
                                $replacestr='<a href="'.$link.'" class="'.$this->cal_ssht_pfx.'-cal-dlink'.'">'.$replace.'</a>';}
                }else{
                        $replacestr=$replace;
                }
                $this->cal_wrk_tmp=ereg_replace ($find, $replacestr, $this->cal_wrk_tmp);
        }
        //generate_calendar_link
        function gen_cal_lnk($l_date){
                 return $this->cal_lnk_add.$this->cal_lnk_cstr.
                         $this->cal_lnk_vprfx.'_date='.(string)$l_date;
        }
        //Gets Year from $cur_date="DD-MM-YYYY";
        function get_year($cur_date,$type){
                $date_split=split("-",$cur_date);
                if ($type=='1'){
                        // Return 2003 Format
                        return date("Y",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
                elseif ($type=='2'){
                        // Return 03 format
                        return date("y",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
        }
        //Gets Month from $cur_date="DD-MM-YYYY";
        function get_month($cur_date,$type){
                $date_split=split("-",$cur_date);
                if ($type=='1'){
                        // Return January format
                        return $this->translate_month($this->cal_lang,date("F",mktime(0,0,0,$date_split[1],$date_split[0],$date_split[2])));}
                elseif ($type=='2'){
                        // Return Jan format
                        return date("M",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
                elseif ($type=='3'){
                        // Return 01 format
                        return date("m",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
                elseif ($type=='4'){
                        // Return 1 format
                        return date("n",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
        }
        //$cur_date="DD-MM-YYYY";
        function get_day($cur_date,$type){
                $date_split=split("-",$cur_date);
                if ($type=='1'){
                        // Return 01 format
                        return date("d",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
                elseif ($type=='2'){
                        // Return 1 format
                        return date("j",mktime (0,0,0,$date_split[1],$date_split[0],$date_split[2]));}
        }
        //Gets the starting day of the week of month $cur_date="DD-MM-YYYY";
        function get_mnt_strt_day($cur_date,$type){
                $date_split=split("-",$cur_date);
                if ($type=='1'){
                         // Return format "0" (Sunday) to "6" (Saturday)
                        return date("w",mktime (0,0,0,$date_split[1],1,$date_split[2]));}
                elseif ($type=='2'){
                         // Return Fri format 
                        return date("D",mktime (0,0,0,$date_split[1],1,$date_split[2]));}
                elseif ($type=='3'){
                         // Return Friday format
                        return date("l",mktime (0,0,0,$date_split[1],1,$date_split[2]));}
        }
        //Gets the number from 0 to 365 for $cur_date="DD-MM-YYYY" month with year position;
        function get_mnt_strt_loc_in_yr($cur_date){
                $date_split=split("-",$cur_date);
                return date("z",mktime (0,0,0,$date_split[1],1,$date_split[2]));
        }

        //Gets the week number
        function get_week_no($cur_date){
                $date_split=split("-",$cur_date);
                return date("W",mktime (0,0,0,$date_split[1],2,$date_split[2]));
        }
        //Gets the date in format "DD-MM-YYYY" for corresponding $cur_date="DD-MM-YYYY" and location in 0 to 365;
        function get_date_frm_loc_in_yr($location_in_year,$cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,1,$location_in_year,$date_split[2]));
        }
        //Gets today date
        function get_today_date(){
                //$timeadjust = ($this->cal_time_hour_diff * 60 * 60);
                //$d_s=split("-",date("H-i-s-m-d-Y"));
                return date("d-m-Y");
        }
        //Gets the next day for $cur_date="DD-MM-YYYY";
        function get_dy_nxt($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,$date_split[1],($date_split[0]+ 1),$date_split[2]));
        }
        //Gets the previuos day for $cur_date="DD-MM-YYYY";
        function get_dy_prev($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,$date_split[1],($date_split[0]-1),$date_split[2]));
        }
        //Gets the previous month for $cur_date="DD-MM-YYYY";
        function get_mnt_prev($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,($date_split[1]-1),$date_split[0],$date_split[2]));
        }
        //Gets the next month for $cur_date="DD-MM-YYYY";
        function get_mnt_nxt($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,($date_split[1]+1),$date_split[0],$date_split[2]));
        }
        //Gets the previous year $cur_date="DD-MM-YYYY";
        function get_yr_prev($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,$date_split[1],$date_split[0],($date_split[2]-1)));
        }
        //gets the next year for $cur_date="DD-MM-YYYY";
        function get_yr_nxt($cur_date){
                $date_split=split("-",$cur_date);
                return date("d-m-Y",mktime (0,0,0,$date_split[1],$date_split[0],($date_split[2]+1)));
        }
        
        //This function transalate for given month. Please add your month accordingly.
        /* By Dirk Olten ( mail@extrabyte.de ) */
        function translate_month($lang,$what){
                if($lang == 'eng') return $what;
                //Dutch Translation contributed by Mariano Iglesias (mariano@cricava.com)
                //Polish Translation contributed by tjagi (tjagi@tomekjar.xo.pl)
                if($lang == 'rus'){
                        switch($what){
                                case 'January': return 'Январь';break;
                                case 'February': return 'Февраль';break;
                                case 'March': return 'Март';break;
                                case 'April': return 'Апрель';break;
                                case 'May': return 'Май';break;
                                case 'June': return 'Июнь';break;
                                case 'July': return 'Июль';break;
                                case 'August': return 'Август';break;
                                case 'September': return 'Сентябрь';break;
                                case 'October': return 'Октябрь';break;
                                case 'November': return 'Ноябрь';break;
                                case 'December': return 'Декабрь';break;
                        }
                }
        }
}
?>
