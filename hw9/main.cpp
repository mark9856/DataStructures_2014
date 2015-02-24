#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include "image.h"

// ===================================================================================================
// ===================================================================================================


void Compress(const Image<Color> &input, 
        Image<bool> &occupancy, Image<Color> &hash_data, Image<Offset> &offset) {

    // you must implement this function

    // Generate occupancy ppm
    int count = 0;
    // Allocate space for occupancy
    occupancy.Allocate(input.Width(), input.Height());
    // if the pixel in input isn't white, this pixel in occupancy should be true
    for(int i = 0; i < input.Width(); ++ i){
        for(int j = 0; j < input.Height(); ++ j){
            if(!input.GetPixel(i, j).isWhite()){
                occupancy.SetPixel(i, j, true);
                count ++;
            }
            else{
                occupancy.SetPixel(i, j, false);
            }
        }
    }

    // Allocate space for offset and hash_data
    //std::cout << "cout: " << count  << std::endl;
    int offset_size = ceil(sqrt(count/4)) + 2;
    int hash_data_size = ceil(sqrt(1.01 * count)) + 1;
    
    // if the input's Width is very small, decrease the hash_data_size and offset_size
    if(hash_data_size >= input.Width() - 3){
        offset_size -= 2; 
        hash_data_size -= 1;
    }
    // if the input's Width is very big, increase the hash_data_size
    if(offset_size > 15){
        hash_data_size += 1;
    }
    
    //std::cout << "offset_size: " << offset_size << std::endl;
    //std::cout << "hash_data_size: " << hash_data_size << std::endl;
    // Allocate space for offset and hash_data
    offset.Allocate(offset_size, offset_size);
    hash_data.Allocate(hash_data_size, hash_data_size);

    // set up offset with total elements
    for(int i = 0; i < input.Width(); ++ i){
        for(int j = 0; j < input.Height(); ++ j){
            if(!input.GetPixel(i, j).isWhite()){
                int si = i % offset.Width(); 
                int sj = j % offset.Width();
                // increase the total number
                int to = offset.GetPixel(si, sj).total;
                to ++;
                Offset tmp;
                tmp.total = to;
                offset.SetPixel(si, sj, tmp);
            }
        }
    }

    // creates an oNodes to store offset_size with total elements
    std::vector<Node> oNodes;
    for(int si = 0; si < offset_size; ++ si){
        for(int sj = 0; sj < offset_size; ++ sj){
            //offsets.push_back(offset.GetPixel(si, sj));
            oNodes.push_back(Node(si, sj, offset.GetPixel(si, sj).total));
            //std::cout << "si: " << si << " sj: " << sj << "total is " << offset.GetPixel(si, sj).total<< std::endl;
        }
    }
    // use the std::sort to sort the oNodes from most total elements to least total elements
    std::sort(oNodes.begin(), oNodes.end(), more_total);
    
    // set the most elements Offset's dx and dy to be 0
    Offset tmp;
    tmp.dx = 0;
    tmp.dy = 0;
    tmp.total = oNodes[0].total;
    offset.SetPixel(oNodes[0].i, oNodes[0].j, tmp);
    //std::cout << "Largest one is: " << oNodes[0].total;

    // for all the elements in the most elements offset, set the corresponding hash_data to store the right Color
    for(int i = 0; i < input.Width(); ++ i){
        for(int j = 0; j < input.Height(); ++ j){
            if(!input.GetPixel(i, j).isWhite()){
                int si = i % offset.Width();
                int sj = j % offset.Width();
                if(si == oNodes[0].i && sj == oNodes[0].j){
                    //std::cout<< "si: " << si << " sj: " << sj << std::endl;
                    //std::cout << "i: " << i%hash_data.Width() << std::endl;
                    hash_data.SetPixel((i + 0)%hash_data.Width(), (j + 0)%hash_data.Width(), input.GetPixel(i, j));
                    //std:: cout << "that is " << i << " " << j << std::endl;
                }
            }
        }
    }

    //std::cout << "hash_data: " << hash_data.Width() << std::endl;
    //std::cout << "oNodes.size: " << oNodes.size() << std::endl;
    // For all the other Nodes beside the Largest one
    for(int k = 1; k < oNodes.size(); ++ k){

        //std::cout << "si: " << oNodes[k].i << " sj: " << oNodes[k].j << "total is " << offset.GetPixel(oNodes[k].i, oNodes[k].j).total<< std::endl;
        // create a Node vector to store all the elements in the same offset Nodes
        std::vector<Node> tNodes;
        for(int i = 0; i < input.Width(); ++ i){
            for(int j = 0; j < input.Height(); ++ j){
                if(!input.GetPixel(i, j).isWhite()){
                    int si = i % offset.Width();
                    int sj = j % offset.Width();
                    if(si == oNodes[k].i && sj == oNodes[k].j){
                        Offset tmp;
                        tmp.total = oNodes[0].total;
                        tNodes.push_back(Node(i, j, 0));
                    }
                }
            }
        }
        //std::cout << "tNodes.size(): "<< tNodes.size() << std::endl;
        
        // create a dNodes vector to store all the possible combination of dx and dy
        std::vector<Node> dNodes;
        // when the offset.Width is less than 15, can set the range less and equal to offset.Width
        if(offset.Width() <= 15){
            for(int i = 0; i <= offset.Width(); ++ i){
                for(int j = 0; j <= offset.Height(); ++ j){
                    dNodes.push_back(Node(i, j, 0));
                }
            }
            
        }
        else{
            for(int j = 0; j <= 15; ++ j){
                for(int i = 0; i <= 15; ++ i){
                    dNodes.push_back(Node(i, j, 0));
                }
            }
        }
        

        int di = 0;
        int dj = 0;
        int m = 0;
        // test all the possible combination of dx and dy till found the one that will have not collision with others
        for(; m < dNodes.size(); ++ m){
            bool found = false;
            for(int l = 0; l < tNodes.size(); ++ l){
                if(!(hash_data.GetPixel((tNodes[l].i + dNodes[m].i)%hash_data.Width(), 
                                (tNodes[l].j + dNodes[m].j)%hash_data.Width()).isWhite())){
                    found = true;
                }
            }
            if(!found){
                di = dNodes[m].i;
                dj = dNodes[m].j;
                break;
            }
        }
        //std::cout << "di: " << di << " dj: " << dj  << std::endl;
        // set up dx and dy
        Offset tOffset;
        tOffset.dx = di;
        tOffset.dy = dj;

        // change the dx and dy 
        offset.SetPixel(oNodes[k].i, oNodes[k].j, tOffset);

        // for all the elements in all offsets, set the corresponding hash_data to store the right Color
        for(int l = 0; l < tNodes.size(); ++ l){
            Color tColor = input.GetPixel(tNodes[l].i, tNodes[l].j);
            hash_data.SetPixel((tNodes[l].i + di)%hash_data.Width(), (tNodes[l].j + dj)%hash_data.Width(), tColor);
        }

        // clear all the tNodes
        tNodes.clear();
    }
}


void UnCompress(const Image<bool> &occupancy, const Image<Color> &hash_data, const Image<Offset> &offset, 
        Image<Color> &output) {

    // you must implement this function


    // Allocate space for output
    output.Allocate(occupancy.Width(), occupancy.Height());
    // find the corresponding color for each output elements
    for(int i = 0; i < occupancy.Width(); ++ i){
        for(int j = 0; j < occupancy.Height(); ++ j){
            if(occupancy.GetPixel(i, j) == true){
                //std::cout<<".";
                int si = i % offset.Width(); 
                int sj = j % offset.Width(); 
                int di = offset.GetPixel(si, sj).dx;
                int dj = offset.GetPixel(si, sj).dy;
                int hi = (i + di) % hash_data.Width(); 
                int hj = (j + dj) % hash_data.Width();
                output.SetPixel(i, j, hash_data.GetPixel(hi, hj));
            }
            else {
                //std::cout<<" ";
            }
        }
        //std::cout<<"\n";

    }
}


// ===================================================================================================
// ===================================================================================================

// Takes in two 24-bit color images as input and creates a b&w output
// image (black where images are the same, white where different)
void Compare(const Image<Color> &input1, const Image<Color> &input2, Image<bool> &output) {

    // confirm that the files are the same size
    if (input1.Width() != input2.Width() ||
            input1.Height() != input2.Height()) {
        std::cerr << "Error: can't compare images of different dimensions: " 
            << input1.Width() << "x" << input1.Height() << " vs " 
            << input2.Width() << "x" << input2.Height() << std::endl;
    } else {
        // make sure that the output images is the right size to store the
        // pixel by pixel differences
        output.Allocate(input1.Width(),input1.Height());
        int count = 0;
        for (int i = 0; i < input1.Width(); i++) {
            for (int j = 0; j < input1.Height(); j++) {
                Color c1 = input1.GetPixel(i,j);
                Color c2 = input2.GetPixel(i,j);
                if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b)
                    output.SetPixel(i,j,true);
                else {
                    count++;
                    output.SetPixel(i,j,false);
                }
            }      
        }     

        // confirm that the files are the same size
        if (count == 0) {
            std::cout << "The images are identical." << std::endl;
        } else {
            std::cout << "The images differ at " << count << " pixel(s)." << std::endl;
        }
    }
}

// ===================================================================================================
// ===================================================================================================

// to allow visualization of the custom offset image format
void ConvertOffsetToColor(const Image<Offset> &input, Image<Color> &output) {
    // prepare the output image to be the same size as the input image
    output.Allocate(input.Width(),input.Height());
    for (int i = 0; i < output.Width(); i++) {
        for (int j = 0; j < output.Height(); j++) {
            // grab the offset value for this pixel in the image
            Offset off = input.GetPixel(i,j);
            // set the pixel in the output image
            int dx = off.dx;
            int dy = off.dy;
            assert (dx >= 0 && dx <= 15);
            assert (dy >= 0 && dy <= 15);
            // to make a pretty image with purple, cyan, blue, & white pixels:
            int red = dx * 16;
            int green = dy *= 16;
            int blue = 255;
            assert (red >= 0 && red <= 255);
            assert (green >= 0 && green <= 255);
            output.SetPixel(i,j,Color(red,green,blue));
        }
    }
}

// ===================================================================================================
// ===================================================================================================

void usage(char* executable) {
    std::cerr << "Usage:  4 options" << std::endl;
    std::cerr << "  1)  " << executable << " compress input.ppm occupancy.pbm data.ppm offset.offset" << std::endl;
    std::cerr << "  2)  " << executable << " uncompress occupancy.pbm data.ppm offset.offset output.ppm" << std::endl;
    std::cerr << "  3)  " << executable << " compare input1.ppm input2.ppm output.pbm" << std::endl;
    std::cerr << "  4)  " << executable << " visualize_offset input.offset output.ppm" << std::endl;
}

// ===================================================================================================
// ===================================================================================================

int main(int argc, char* argv[]) {
    if (argc < 2) { usage(argv[1]); exit(1); }

    if (argv[1] == std::string("compress")) {
        if (argc != 6) { usage(argv[1]); exit(1); }
        // the original image:
        Image<Color> input;
        // 3 files form the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        input.Load(argv[2]);
        Compress(input,occupancy,hash_data,offset);
        // save the compressed representation
        occupancy.Save(argv[3]);
        hash_data.Save(argv[4]);
        offset.Save(argv[5]);

    } else if (argv[1] == std::string("uncompress")) {
        if (argc != 6) { usage(argv[1]); exit(1); }
        // the compressed representation:
        Image<bool> occupancy;
        Image<Color> hash_data;
        Image<Offset> offset;
        occupancy.Load(argv[2]);
        hash_data.Load(argv[3]);
        offset.Load(argv[4]);
        // the reconstructed image
        Image<Color> output;
        UnCompress(occupancy,hash_data,offset,output);
        // save the reconstruction
        output.Save(argv[5]);

    } else if (argv[1] == std::string("compare")) {
        if (argc != 5) { usage(argv[1]); exit(1); }
        // the original images
        Image<Color> input1;
        Image<Color> input2;    
        input1.Load(argv[2]);
        input2.Load(argv[3]);
        // the difference image
        Image<bool> output;
        Compare(input1,input2,output);
        // save the difference
        output.Save(argv[4]);

    } else if (argv[1] == std::string("visualize_offset")) {
        if (argc != 4) { usage(argv[1]); exit(1); }
        // the 8-bit offset image (custom format)
        Image<Offset> input;
        input.Load(argv[2]);
        // a 24-bit color version of the image
        Image<Color> output;
        ConvertOffsetToColor(input,output);
        output.Save(argv[3]);

    } else {
        usage(argv[0]);
        exit(1);
    }
}

// ===================================================================================================
// ===================================================================================================
