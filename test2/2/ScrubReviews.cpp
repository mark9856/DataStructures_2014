void ScrubReviews(std::list<std::vector<std::string>> & reviews, const std::string & word){
    for(std::list<std::vector<std::string>>::iterator lst_itr = reviews.begin(); 
            lst_itr != reviews.end(); ++ lst_itr){
        for(std::vector<std::string>::iterator vec_itr = *lst_itr; vec_itr != *lst_itr.end(); ++ vec_itr){
            if(*vec_itr == word){
                if(vec_itr != *lst_itr.end()){
                    *vec_itr = *(vec_itr + 1);
                }
            }

        }
    }
}
