//
//  Scrittura_m_files.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 20/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//
//**************************************************************************************

#include <iostream>
#include <fstream>

void Scrittura_m_filesAutomatic();

using namespace std;

/**
 * This function write the .m files. If you want to add a new .m files.
 * To add new functions you might use the program mintocpp.cpp which do the conversion that you can paste here.
 */

void Scrittura_m_files(){
    
    ofstream file1("Caricamento_filmato_hist.m");
    ofstream file2("Movie_Matlab_from_cpp.m");
    ofstream file3("functionC.m");
    ofstream file4("hist3.m");
    ofstream file5("Evolution_Mass_center.m");
    ofstream file6("Movie_Matlab_from_cpp_and_single.m");
    ofstream file7("functionC1.m");
    ofstream file8("traiettorie_singole.m");
    ofstream file9("Filmatohist.m");
    ofstream file10("Save_Movie_avi.m");
    ofstream file11("function_c.m");
    ofstream file12("MovieCpp2matlab.m");
    ofstream file13("distribuzione_tempi.m");
    ofstream file14("getkey.m");
    //**************************************************************************************
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Caricamento_filmato_hist.m
    //**************************************************************************************
    
    
    {
        file1 << "function [D,b,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd,mesh_,r)  " << endl 
        << "a=cell(1,2);  " << endl 
        << "D=cell(1,r);  " << endl 
        << "% % % a{1,1}=round(mesh_(1)):round(hd):round(mesh_(2));  " << endl 
        << "% % % a{1,2}=round(mesh_(3)):round(hd):round(mesh_(4));  " << endl 
        << "clc  " << endl 
        << "fprintf('\\n\\n     --------- LOADING FILM!!! --------\\n\\n')  " << endl 
        << "  " << endl 
        << "%fprintf('--------- RUBERESTI MAI UN'AUTO? -----------\\n\\n')  " << endl 
        << "%fprintf('\\n\\n       ...Caricamento Filmato...\\n\\n')  " << endl 
        << "%fprintf('\\n\\n--------- NON COMPRARE DVD PIRATA, ARRRGH --------\\n\\n')  " << endl 
        << "tic  " << endl 
        << "a{1,1}=mesh_(1):hd(1):mesh_(2);  " << endl 
        << "  " << endl 
        << "if isempty(a{1,1})  " << endl 
        << "    a{1,1}=linspace(mesh_(1),mesh_(2),4);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "a{1,2}=mesh_(3):hd(2):mesh_(4);  " << endl 
        << "  " << endl 
        << "if isempty(a{1,2})  " << endl 
        << "    a{1,2}=linspace(mesh_(3),mesh_(4),4);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "% Z_max_=3;  " << endl 
        << "  " << endl 
        << "max_Z_temp=zeros(r,1);  " << endl 
        << "  " << endl 
        << "for i=1:r  " << endl 
        << "    [N,b]=hist3(P(:,:,i)','Edges',a);  " << endl 
        << "	D{1,i}=N;  " << endl 
        << "    max_Z_temp(i)=max(max(N));  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "fprintf('\\n\\n     --------- END LOADING FILM!!! --------\\n\\n')  " << endl 
        << "pause(1)  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "% Z_max_=max(max(N));  " << endl 
        << "Z_max_fin =max(max(N));  " << endl 
        << "Z_max_=max(max_Z_temp)+1;  " << endl 
        << "  " << endl 
        << "scrsz = get(0,'ScreenSize');  " << endl 
        << "figure('Position', [scrsz(3) scrsz(4) scrsz(3)/3 scrsz(4)/3])  " << endl 
        << "plot(1:r,max_Z_temp)  " << endl 
        << "axis([0 r 0 Z_max_])  " << endl 
        << "grid on  " << endl 
        << "% input('\\nPress a key to continue : ','s');  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Movie_Matlab_from_cpp.m
    //**************************************************************************************
    
    {
        file2 << "function [] = Movie_Matlab_from_cpp()  " << endl 
        << "%UNTITLED Summary of this function goes here  " << endl 
        << "%   Detailed explanation goes here  " << endl 
        << "  " << endl 
        << "n=load('file_matlab.txt');" << endl
        << "m=n(2)-n(1)" << endl
        << "for i=0:n(1)-1" << endl
        << "    m=m+1;" << endl
        << "    MovieCpp2matlab(i,m)  " << endl
        << "end" << endl
        << "exit;  " << endl 
        << "%fprintf('\\ntype exit to quit ... \\n');  " << endl 
        << "  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // functionC.m
    //**************************************************************************************
    
    
    {
        file3 << "function [c,x,y] = functionC(M,t,T,num_funz)  " << endl 
        << "n_mesh_punt=80;  " << endl 
        << "[x,y]=meshgrid(linspace(M(1),M(2),n_mesh_punt),linspace(M(3),M(4),n_mesh_punt));  " << endl 
        << "  " << endl 
        << "switch num_funz  " << endl 
        << "      " << endl 
        << "    case 0  " << endl 
        << "         " << endl 
        << "        sigma=10;  " << endl 
        << "          " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "        c = 1+6*exp(-R.^2/sigma);  " << endl 
        << "         " << endl 
        << "    case 1 " << endl 
        << "         " << endl 
        << "        T=15;         " << endl 
        << "        c=1+1.*(0*x.*y)+2*(t>T); " << endl 
        << "     " << endl 
        << "    case 2  " << endl 
        << " " << endl 
        << "          " << endl 
        << "        T=100;  " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "        c = 1+(R<8).*1.2.*abs((1+(t)/T).*sin(2*pi*(R+2*(t)/T)/2)./(R+(t)/T))...  " << endl 
        << "            +.8*(R>=8).*(R<16).*abs(cos(atan(sin(R)+t/T)))...  " << endl 
        << "            +(R>=16).*.1.*abs((1+(t)/T).*cos(sqrt(abs(y))).*atan((x.^2)).*sin(R+1.1*pi*((t)/T)));  " << endl 
        << "      " << endl 
        << "    case 3  " << endl 
        << " " << endl 
        << "        c= 1.*(0*x.*y)+ 1+2*(t<=6)+7*(t>6)*(t<=6+1)*pow(t-6,2)+7*(t>6+1); " << endl 
        << "         " << endl 
        << "    case 4  " << endl 
        << "         " << endl 
        << "        c= 1.*(0*x.*y)+ 1+7*(t<8)+(t>=15)*(t<25)+3*(t>25); " << endl 
        << "          " << endl 
        << "    case 5  " << endl 
        << "         " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps; " << endl 
        << "        c = 3*(1+max(R,x)/2); " << endl 
        << "      " << endl 
        << "    case 6  " << endl 
        << "         " << endl 
        << "        c= 18.2*exp(10*x); " << endl 
        << "                  " << endl 
        << "	case 7  " << endl 
        << "         " << endl 
        << "        c = 0*x+18.2*exp(0.2*t); " << endl 
        << "        " << endl 
        << "    otherwise " << endl 
        << "         " << endl 
        << "        c=1+0.*x; " << endl 
        << " " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // hist3.m
    //**************************************************************************************
    
    
    {
        file4 << "function [nn,ctrs] = hist3(varargin)  " << endl 
        << "%HIST3 Three-dimensional histogram of bivariate data.  " << endl 
        << "%   HIST3(X) bins the elements of the M-by-2 matrix X into a 10-by-10 grid  " << endl 
        << "%   of equally-spaced containers, and plots a histogram.  Each column of X  " << endl 
        << "%   corresponds to one dimension in the bin grid.  " << endl 
        << "%  " << endl 
        << "%   HIST3(X,NBINS) plots a histogram using an NBINS(1)-by-NBINS(2) grid of  " << endl 
        << "%   bins.  HIST3(X,'Nbins',NBINS) is equivalent to HIST3(X,NBINS).  " << endl 
        << "%  " << endl 
        << "%   HIST3(X,CTRS), where CTRS is a two-element cell array of numeric  " << endl 
        << "%   vectors with monotonically non-decreasing values, uses a 2D grid of  " << endl 
        << "%   bins centered on CTRS{1} in the first dimension and on CTRS{2} in the  " << endl 
        << "%   second.  HIST3 assigns rows of X falling outside the range of that grid  " << endl 
        << "%   to the bins along the outer edges of the grid, and ignores rows of X  " << endl 
        << "%   containing NaNs.  HIST3(X,'Ctrs',CTRS) is equivalent to HIST3(X,CTRS).  " << endl 
        << "%  " << endl 
        << "%   HIST3(X,'Edges',EDGES), where EDGES is a two-element cell array  " << endl 
        << "%   of numeric vectors with monotonically non-decreasing values, uses a 2D  " << endl 
        << "%   grid of bins with edges at EDGES{1} in the first dimension and at  " << endl 
        << "%   EDGES{2} in the second.  The (i,j)-th bin includes the value X(k,:) if  " << endl 
        << "%  " << endl 
        << "%      EDGES{1}(i) <= X(k,1) < EDGES{1}(i+1) and  " << endl 
        << "%      EDGES{2}(j) <= X(k,2) < EDGES{2}(j+1).  " << endl 
        << "%  " << endl 
        << "%   Rows of X that that fall on the upper edges of the grid, EDGES{1}(end)  " << endl 
        << "%   or EDGES{2}(end), are counted in the (I,j)-th or (i,J)-th bins, where  " << endl 
        << "%   I and J are the lengths of EDGES{1} and EDGES{2}.  HIST3 does not count  " << endl 
        << "%   rows of X falling outside the range of the grid.  Use -Inf and Inf in  " << endl 
        << "%   EDGES to include all non-NaN values.  " << endl 
        << "%  " << endl 
        << "%   N = HIST3(X,...) returns a matrix containing the number of elements of  " << endl 
        << "%   X that fall in each bin of the grid, and does not plot the histogram.  " << endl 
        << "%     " << endl 
        << "%   [N,C] = HIST3(X,...) returns the positions of the bin centers in a  " << endl 
        << "%   1-by-2 cell array of numeric vectors, and does not plot the histogram.  " << endl 
        << "%  " << endl 
        << "%   HIST3(AX,X,...) plots into AX instead of GCA.  " << endl 
        << "%  " << endl 
        << "%   HIST3(..., 'PARAM1',val1, 'PARAM2',val2, ...) allows you to specify  " << endl 
        << "%   graphics parameter name/value pairs to fine-tune the plot.  " << endl 
        << "%  " << endl 
        << "%   Examples:  " << endl 
        << "%  " << endl 
        << "%      % Create the car data and make a histogram on a 7x7 grid of bins.  " << endl 
        << "%      load carbig  " << endl 
        << "%      X = [MPG,Weight];  " << endl 
        << "%      hist3(X,[7 7]);  " << endl 
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl 
        << "%  " << endl 
        << "%      % Make a histogram with semi-transparent bars  " << endl 
        << "%      hist3(X,[7 7],'FaceAlpha',.65);  " << endl 
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl 
        << "%      set(gcf,'renderer','opengl');  " << endl 
        << "%  " << endl 
        << "%      % Make a histogram with bars colored according to height  " << endl 
        << "%      hist3(X,[7 7]);  " << endl 
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl 
        << "%      set(gcf,'renderer','opengl');  " << endl 
        << "%      set(get(gca,'child'),'FaceColor','interp','CDataMode','auto');  " << endl 
        << "%  " << endl 
        << "%      % Specify bin centers, different in each direction.  Get back  " << endl 
        << "%      % counts, but don't make the plot.  " << endl 
        << "%      cnt = hist3(X, {0:10:50 2000:500:5000});  " << endl 
        << "%  " << endl 
        << "%   See also ACCUMARRAY, BAR, BAR3, HIST, HISTC.  " << endl 
        << "  " << endl 
        << "%   Copyright 1993-2009 The MathWorks, Inc.  " << endl 
        << "%   $Revision: 1.1.8.3 $  $Date: 2011/05/09 01:25:19 $  " << endl 
        << "  " << endl 
        << "[cax,args,nargs] = axescheck(varargin{:});  " << endl 
        << "  " << endl 
        << "if nargs < 1  " << endl 
        << "    error(message('stats:hist3:TooFewInputs'))  " << endl 
        << "end  " << endl 
        << "x = args{1};  " << endl 
        << "   " << endl 
        << "% See if nbins/ctrs was given as the second argument, or only name/value  " << endl 
        << "% pairs.  " << endl 
        << "if nargs > 1 && ~ischar(args{2})  " << endl 
        << "    binSpec = args{2};  " << endl 
        << "    args = args(3:end); % strip off x and nbins/ctrs  " << endl 
        << "else  " << endl 
        << "    binSpec = [];  " << endl 
        << "    args = args(2:end); % strip off x  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "% Process input parameter name/value pairs, assume unrecognized ones are  " << endl 
        << "% graphics properties.  " << endl 
        << "pnames = {'nbins','ctrs','edges'};  " << endl 
        << "dflts =  { [],     [],       []};  " << endl 
        << "[nbins,ctrs,edges,~,plotArgs] = internal.stats.parseArgs(pnames,dflts,args{:});  " << endl 
        << "  " << endl 
        << "% Make sure they haven't mixed 'nbins'/'ctrs'/'edges' name/value pairs with  " << endl 
        << "% the CTRS or NBINS unnamed second arg syntax, or used more than one of  " << endl 
        << "% those parameter name/value pairs.  " << endl 
        << "if (isempty(nbins)+isempty(ctrs)+isempty(edges)+isempty(binSpec)) < 3  " << endl 
        << "    error(message('stats:hist3:AmbiguousBinSpec'));  " << endl 
        << "elseif ~isempty(binSpec)  " << endl 
        << "    if iscell(binSpec)  % hist3(x,ctrs)  " << endl 
        << "        ctrs = binSpec;  " << endl 
        << "    else                % hist3(x,nbins)  " << endl 
        << "        nbins = binSpec;  " << endl 
        << "    end  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "if ~isempty(nbins)  " << endl 
        << "    % Use the specified number of bars in each direction, centers and edges  " << endl 
        << "    % to be determined.  " << endl 
        << "    histBehavior = true;  " << endl 
        << "    if ~(isnumeric(nbins) && numel(nbins)==2)  " << endl 
        << "        error(message('stats:hist3:BadNbins'));  " << endl 
        << "    end  " << endl 
        << "    autobins = true;  " << endl 
        << "      " << endl 
        << "elseif ~isempty(ctrs)  " << endl 
        << "    % Use the specified bin centers.  " << endl 
        << "    histBehavior = true;  " << endl 
        << "    if ~(iscell(ctrs) && numel(ctrs)==2 && isnumeric(ctrs{1}) && isnumeric(ctrs{2}))  " << endl 
        << "        error(message('stats:hist3:BadCtrs'));  " << endl 
        << "    end  " << endl 
        << "    ctrs = {ctrs{1}(:)' ctrs{2}(:)'};  " << endl 
        << "    autobins = false;  " << endl 
        << "    nbins = [length(ctrs{1}) length(ctrs{2})];  " << endl 
        << "      " << endl 
        << "elseif ~isempty(edges)  " << endl 
        << "    % Use the specified bin edges.  " << endl 
        << "    histBehavior = false;  " << endl 
        << "    if ~(iscell(edges) && numel(edges)==2 && isnumeric(edges{1}) && isnumeric(edges{2}))  " << endl 
        << "        error(message('stats:hist3:BadEdges'));  " << endl 
        << "    end  " << endl 
        << "    edges = {edges{1}(:)' edges{2}(:)'};  " << endl 
        << "    autobins = false;  " << endl 
        << "    % Just as with histc, there will be #edges bins  " << endl 
        << "    nbins = [length(edges{1}) length(edges{2})];  " << endl 
        << "      " << endl 
        << "else  " << endl 
        << "    % Assume a 10x10 grid of bars, centers and edges to be determined.  " << endl 
        << "    histBehavior = true;  " << endl 
        << "    autobins = true;  " << endl 
        << "    nbins = [10 10];  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "[nrows,ncols] = size(x);  " << endl 
        << "if ncols ~= 2  " << endl 
        << "    error(message('stats:hist3:WrongNumCols'));  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "% Special case for empty data (follows what HIST does).  " << endl 
        << "if isempty(x)  " << endl 
        << "    if autobins  " << endl 
        << "       ctrs = {1:nbins(1) 1:nbins(2)};  " << endl 
        << "    end  " << endl 
        << "    n = zeros(nbins); % Nothing to count, return nbins(1) by nbins(2) zeros  " << endl 
        << "      " << endl 
        << "else  " << endl 
        << "    % Bin each observation in the x-direction, and in the y-direction.  " << endl 
        << "    bin = zeros(nrows,2);  " << endl 
        << "    for i = 1:2  " << endl 
        << "        minx = min(x(:,i));  " << endl 
        << "        maxx = max(x(:,i));  " << endl 
        << "          " << endl 
        << "        % If only the number of bins was given, compute edges and centers  " << endl 
        << "        % for equal-sized bins spanning the data.  " << endl 
        << "        if autobins  " << endl 
        << "            if isinf(minx) || isinf(maxx)  " << endl 
        << "                error(message('stats:hist3:InfData'));  " << endl 
        << "            elseif minx == maxx  " << endl 
        << "                minx = minx - floor(nbins(i)/2) - 0.5;  " << endl 
        << "                maxx = maxx + ceil(nbins(i)/2) - 0.5;  " << endl 
        << "            end  " << endl 
        << "            binwidth{i} = (maxx - minx) / nbins(i);  " << endl 
        << "            edges{i} = minx + binwidth{i}*(0:nbins(i));  " << endl 
        << "            ctrs{i} = edges{i}(1:nbins(i)) + binwidth{i}/2;  " << endl 
        << "            % Make histc mimic hist behavior:  everything < ctrs(1) gets  " << endl 
        << "            % counted in first bin, everything > ctrs(end) gets counted in  " << endl 
        << "            % last bin.  ctrs, edges, and binwidth do not reflect that, but  " << endl 
        << "            % histcEdges does.  " << endl 
        << "            histcEdges = [-Inf edges{i}(2:end-1) Inf];  " << endl 
        << "              " << endl 
        << "        % If the bin centers were given, compute their edges and widths.  " << endl 
        << "        elseif histBehavior  " << endl 
        << "            c = ctrs{i};  " << endl 
        << "            dc = diff(c);  " << endl 
        << "            edges{i} = [c(1) c] + [-dc(1) dc dc(end)]/2;  " << endl 
        << "            binwidth{i} = diff(edges{i});  " << endl 
        << "            % Make histc mimic hist behavior:  everything < ctrs(1) gets  " << endl 
        << "            % counted in first bin, everything > ctrs(end) gets counted in  " << endl 
        << "            % last bin.  ctrs, edges, and binwidth do not reflect that, but  " << endl 
        << "            % histcEdges does.  " << endl 
        << "            histcEdges = [-Inf edges{i}(2:end-1) Inf];  " << endl 
        << "              " << endl 
        << "        % If the bin edges were given, compute their widths and centers (if  " << endl 
        << "        % asked for).  " << endl 
        << "        else % if ~histBehavior  " << endl 
        << "            e = edges{i};  " << endl 
        << "            de = diff(e);  " << endl 
        << "            histcEdges = e;  " << endl 
        << "            % Make the display mimic bar's histc behavior: an implied bin  " << endl 
        << "            % above edges(end), the same width as the last explicit one.  " << endl 
        << "            % ctrs, edges, and binwidth need that explicitly, histcEdges  " << endl 
        << "            % doesn't.  " << endl 
        << "            edges{i} = [e e(end)+de(end)];  " << endl 
        << "            binwidth{i} = [de de(end)];  " << endl 
        << "            if nargout > 1  " << endl 
        << "                c = zeros(size(de));  " << endl 
        << "                c(1) = e(1) + de(1)/2;  " << endl 
        << "                for j = 2:length(c)  " << endl 
        << "                    c(j) = 2*e(j) - c(j-1);  " << endl 
        << "                end  " << endl 
        << "                % When edges are specified, it may not be possible to return  " << endl 
        << "                % centers for which the edges are midpoints.  Warn if that's  " << endl 
        << "                % the case.  " << endl 
        << "                if any(c <= e(1:end-1)) || ...  " << endl 
        << "                   abs(c(end) - (e(end)-de(end)/2)) > 1000*eps(de(end));  " << endl 
        << "                    warning(message('stats:hist3:InconsistentEdges'));  " << endl 
        << "                    c = e(1:end-1) + de/2;  " << endl 
        << "                end  " << endl 
        << "                ctrs{i} = [c e(end)+de(end)/2];  " << endl 
        << "            end  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        % Get the 1D bin numbers for this column of x.  Make sure +Inf  " << endl 
        << "        % goes into the nth bin, not the (n+1)th.  " << endl 
        << "        [dum,bin(:,i)] = histc(x(:,i),histcEdges,1);  " << endl 
        << "        bin(:,i) = min(bin(:,i),nbins(i));  " << endl 
        << "    end  " << endl 
        << "      " << endl 
        << "    % Combine the two vectors of 1D bin counts into a grid of 2D bin  " << endl 
        << "    % counts.  " << endl 
        << "    n = accumarray(bin(all(bin>0,2),:),1,nbins);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "if 0 < nargout  " << endl 
        << "    nn = n;  " << endl 
        << "    return  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "del = .001; % space between bars, relative to bar size  " << endl 
        << "  " << endl 
        << "% Build x-coords for the eight corners of each bar.  " << endl 
        << "xx = edges{1};  " << endl 
        << "xx = [xx(1:nbins(1))+del*binwidth{1}; xx(2:nbins(1)+1)-del*binwidth{1}];  " << endl 
        << "xx = [reshape(repmat(xx(:)',2,1),4,nbins(1)); NaN(1,nbins(1))];  " << endl 
        << "xx = [repmat(xx(:),1,4) NaN(5*nbins(1),1)];  " << endl 
        << "xx = repmat(xx,1,nbins(2));  " << endl 
        << "  " << endl 
        << "% Build y-coords for the eight corners of each bar.  " << endl 
        << "yy = edges{2};  " << endl 
        << "yy = [yy(1:nbins(2))+del*binwidth{2}; yy(2:nbins(2)+1)-del*binwidth{2}];  " << endl 
        << "yy = [reshape(repmat(yy(:)',2,1),4,nbins(2)); NaN(1,nbins(2))];  " << endl 
        << "yy = [repmat(yy(:),1,4) NaN(5*nbins(2),1)];  " << endl 
        << "yy = repmat(yy',nbins(1),1);  " << endl 
        << "  " << endl 
        << "% Build z-coords for the eight corners of each bar.  " << endl 
        << "zz = zeros(5*nbins(1), 5*nbins(2));  " << endl 
        << "zz(5*(1:nbins(1))-3, 5*(1:nbins(2))-3) = n;  " << endl 
        << "zz(5*(1:nbins(1))-3, 5*(1:nbins(2))-2) = n;  " << endl 
        << "zz(5*(1:nbins(1))-2, 5*(1:nbins(2))-3) = n;  " << endl 
        << "zz(5*(1:nbins(1))-2, 5*(1:nbins(2))-2) = n;  " << endl 
        << "  " << endl 
        << "cax = newplot(cax);  " << endl 
        << "holdState = ishold(cax);  " << endl 
        << "  " << endl 
        << "% Plot the bars in a light steel blue.  " << endl 
        << "cc = repmat(cat(3,.75,.85,.95), [size(zz) 1]);  " << endl 
        << "  " << endl 
        << "% Plot the surface, using any specified graphics properties to override  " << endl 
        << "% defaults.  " << endl 
        << "h = surf(cax, xx, yy, zz, cc, 'tag','hist3', plotArgs{:});  " << endl 
        << "  " << endl 
        << "if ~holdState  " << endl 
        << "    % Set ticks for each bar if fewer than 16 and the centers/edges are  " << endl 
        << "    % integers.  Otherwise, leave the default ticks alone.  " << endl 
        << "    if (nbins(1)<16)  " << endl 
        << "        if histBehavior && all(floor(ctrs{1})==ctrs{1})  " << endl 
        << "            set(cax,'xtick',ctrs{1});  " << endl 
        << "        elseif ~histBehavior && all(floor(edges{1})==edges{1})  " << endl 
        << "            set(cax,'xtick',edges{1});  " << endl 
        << "        end  " << endl 
        << "    end  " << endl 
        << "    if (nbins(2)<16)  " << endl 
        << "        if histBehavior && all(floor(ctrs{2})==ctrs{2})  " << endl 
        << "            set(cax,'ytick',ctrs{2});  " << endl 
        << "        elseif ~histBehavior && all(floor(edges{2})==edges{2})  " << endl 
        << "            set(cax,'ytick',edges{2});  " << endl 
        << "        end  " << endl 
        << "    end  " << endl 
        << "      " << endl 
        << "    % Set the axis limits to have some space at the edges of the bars.  " << endl 
        << "    dx = range(edges{1})*.05;  " << endl 
        << "    dy = range(edges{2})*.05;  " << endl 
        << "    set(cax,'xlim',[edges{1}(1)-dx edges{1}(end)+dx]);  " << endl 
        << "    set(cax,'ylim',[edges{2}(1)-dy edges{2}(end)+dy]);  " << endl 
        << "      " << endl 
        << "    view(cax,3);  " << endl 
        << "    grid(cax,'on');  " << endl 
        << "    set(get(cax,'parent'),'renderer','zbuffer');  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "if nargout > 0  " << endl 
        << "    nn = n;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Evolution_Mass_center.m
    //**************************************************************************************
    
    
    {
        file5 << "function [] = Evolution_Mass_center(P,dim_P_Temp)  " << endl 
        << "%EVOLUTION_MASS_CENTER Summary of this function goes here  " << endl 
        << "%   Detailed explanation goes here  " << endl 
        << "  " << endl 
        << "    P_mean=zeros(2,dim_P_Temp);  " << endl 
        << "      " << endl 
        << "    for i=1:dim_P_Temp  " << endl 
        << "        P_mean(1,i)=mean(P(1,:,i));  " << endl 
        << "        P_mean(2,i)=mean(P(2,:,i));  " << endl 
        << "    end  " << endl 
        << "  " << endl 
        << "    MsupP=[min(P_mean(1,:))-.02 max(P_mean(1,:))+.02 min(P_mean(2,:))-.02 max(P_mean(2,:))+.02];  " << endl 
        << "      " << endl 
        << "    plot(P_mean(1,:),P_mean(2,:));  " << endl 
        << "    axis(MsupP)  " << endl 
        << "    hold on  " << endl 
        << "    plot(P_mean(1,1),P_mean(2,1),'g*','LineWidth',4);  " << endl 
        << "    plot(P_mean(1,floor(end/2)),P_mean(2,floor(end/2)),'y*','LineWidth',4);  " << endl 
        << "    plot(P_mean(1,end),P_mean(2,end),'k*','LineWidth',4);  " << endl 
        << "    title(['Trajectory center of mass of the population: Green=start;Yellow=middle;Black=end']);  " << endl 
        << "    grid on  " << endl 
        << "    hold off  " << endl 
        << "  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Movie_Matlab_from_cpp_and_single.m
    //**************************************************************************************
    
    
    {
        file6 << "function [] = Movie_Matlab_from_cpp_and_single()  " << endl 
        << "%UNTITLED Summary of this function goes here  " << endl 
        << "%   Detailed explanation goes here  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "MovieCpp2matlab;  " << endl 
        << "exit;  " << endl 
        << "%fprintf('\\ntype exit to quit ... \\n');  " << endl 
        << "  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // functionC1.m
    //**************************************************************************************
    
    
    {
        file7 << "function [c,x,y] = functionC1(X_x,M,t,T,num_funz)  " << endl 
        << "n_mesh_punt=200;  " << endl 
        << "[x,y]=meshgrid(X_x,linspace(M(3),M(4),n_mesh_punt));  " << endl 
        << "  " << endl 
        << "switch num_funz  " << endl 
        << "      " << endl 
        << "    case 1  " << endl 
        << "        %% SOMBRERO ONDEGGIANTE  " << endl 
        << "% % %         T=T/3;  " << endl 
        << "  " << endl 
        << "% % %         T=100;  " << endl 
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "% % %         c = 1+6*abs((1+(t)/T).*sin((R+2*(t)/T)/2)./(R+(t)/T));  " << endl 
        << "          " << endl 
        << "        T=30;  " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "        c = 1+(R<8).*1.2.*abs((1+(t)/T).*sin(2*pi*(R+2*(t)/T)/2)./(R+(t)/T))...  " << endl 
        << "            +.8*(R>=8).*(R<16).*abs(cos(atan(sin(R)+t/T)))...  " << endl 
        << "            +(R>=16).*.1.*abs((1+(t)/T).*cos(sqrt(abs(y))).*atan((x.^2)).*sin(R+1.1*pi*((t)/T)));  " << endl 
        << "  " << endl 
        << "% % %         T=400;  " << endl 
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "% % %         c = pi+(1+atan(cos(R.^2))).*sin(R+8*(t-1)/T);  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "% % %         T=600;  " << endl 
        << "% % %         T=T/3;  " << endl 
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "% % %         if t<=T/2  " << endl 
        << "% % %             c = 1+6*abs((1+(t-1)/(5*T)).*sin(R+2*(t-1)/(5*T))./(R+2*(t-1)/(5*T)));  " << endl 
        << "% % %         else  " << endl 
        << "% % %             c = 1+5*exp(-(t-T/2)/T)*6*abs((1+(t-1)/(5*T)).*sin(R+2*(t-1)/(5*T))./(R+2*(t-1)/(5*T)));  " << endl 
        << "% % %         end  " << endl 
        << "          " << endl 
        << "% % %         T=600;  " << endl 
        << "% % %         T=T/3;  " << endl 
        << "% % % 	      R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "% % %         c = 1+(1+abs(tan(R))).*exp(T-t).*abs((1+(t-1)/T).*sin(R+2*(t-1)/T)./(R+2*(t-1)/T));  " << endl 
        << "  " << endl 
        << "          " << endl 
        << "% % %         %% VIDEO GLOBALE  " << endl 
        << "% % %         mesh_=47.1163;  " << endl 
        << "% % %         [X1,Y] = meshgrid(-mesh_:.1:mesh_);  " << endl 
        << "% % %         R = sqrt(X1.^2 + Y.^2) + eps;  " << endl 
        << "% % %         c =5*abs((1+(t-1)/T)*sin(R+(t-1)/T)./(R+(t-1)/T));  " << endl 
        << "% % %         contour(X1,Y,c)  " << endl 
        << "      " << endl 
        << "    case 2  " << endl 
        << "        %% GAUSSIAN  " << endl 
        << "        sigma=100;  " << endl 
        << "          " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "        c = 1+2*exp(-R.^2/sigma);  " << endl 
        << "      " << endl 
        << "    case 3  " << endl 
        << "        T=T/3;  " << endl 
        << "        %% CONST >> CRESCE  " << endl 
        << "%      c = 0*sqrt(x.^2 + 1)*exp(-y.^2/(t+1));  " << endl 
        << "%      c=exp(-t/80)*abs(.1*x+t/10*sin(y));  " << endl 
        << "%      c=abs(.1*x+t/(T)*sin(y));  " << endl 
        << "%     c=abs(.1*x+3*sin(R)-(.1*x+(t-50)/10*sin(y)));  " << endl 
        << "%     c=abs(.1*x+3*sin(R)-(.1*x+(t-30)/10*sin(R)));  " << endl 
        << "%      c=(t>=5)*abs(5*(1+(t-1)/100)*sin(R+(t-1)/100)./(R+(t-1)/100))+...  " << endl 
        << "%          (t<5)*0*x;  " << endl 
        << "%      c=(t<=5)*0*sin(R)+(t>5)*(3+0*sin(R+(t-1)/100));  " << endl 
        << "%      c =3+zeros(1,dim_cell/2);  " << endl 
        << "  " << endl 
        << "     c=1.*(0*x.*y)+(t<=T)*0+(t>T)*(t<=T+1)*(t-T)^2+(t>T+1);  " << endl 
        << "         " << endl 
        << "    case 4  " << endl 
        << "        %% CONST>>DECRESCE  " << endl 
        << "        c=1.*(0*x.*y)+(t<=T)+(t>T)*(t<=T+1)*(t-T-1)^2+(t>T+1)*0;  " << endl 
        << "          " << endl 
        << "    case 5  " << endl 
        << "        %% SUPP COMPATTO GAUSSIANA  " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "        c = 1+2*exp(-R.^2/10).*(abs(R)<=5);  " << endl 
        << "      " << endl 
        << "    case 6  " << endl 
        << "        %% CONST>> CRESC. DECRESC.  " << endl 
        << "        c=1.*(0*x.*y)+(t<T/3)*0+(t>=T/3)*(t<2*T/3)+(t>2*T/3)*0;  " << endl 
        << "                  " << endl 
        << "	case 7  " << endl 
        << "        sigma=5;  " << endl 
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "%         c = 1 + 3*exp(-R.^2/100).*(R<=20)+.5246*exp(-(R-40).^2/100).*(R>20)+.5*(R>20);  " << endl 
        << "%         c = 1 + 3*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl 
        << "        T=200;c = 1 + (sin(4*pi*t/T)+1).*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl 
        << "      " << endl 
        << "    case 8  " << endl 
        << "          " << endl 
        << "        if (t<=T/5)  " << endl 
        << "                num_funz=1;  " << endl 
        << "                [c,x,y]=functionC(M,5*t,T,num_funz);  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        if (t<=2*T/5 && t>T/5)  " << endl 
        << "                num_funz=6;  " << endl 
        << "                [c,x,y]=functionC(M,5*(t-T/5),T,num_funz);  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        if (t<=3*T/5 && t>2*T/5)   " << endl 
        << "                num_funz=7;  " << endl 
        << "                [c,x,y]=functionC(M,5*(t-2*T/5),T,num_funz);  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        if (t<=4*T/5 && t>3*T/5)   " << endl 
        << "                num_funz=2;  " << endl 
        << "                [c,x,y]=functionC(M,5*(t-3*T/5),T,num_funz);  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        if (t>4*T/5)   " << endl 
        << "                num_funz=1;  " << endl 
        << "                [c,x,y]=functionC(M,5*(t-4*T/5),T,num_funz);  " << endl 
        << "        end  " << endl 
        << "  " << endl 
        << "    otherwise  " << endl 
        << "        c=0.*x;  " << endl 
        << "%         sigma=5;  " << endl 
        << "%         R = sqrt(x.^2 + y.^2) + eps;  " << endl 
        << "%         T=200;c = 1 + (sin(4*pi*t/T)+1).*exp(-R.^2/sigma).*(R<=5)+atan(x).*sin(3*pi*t/T)*(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // traiettorie_singole.m
    //**************************************************************************************
    
    
    {
        file8 << "function [] = traiettorie_singole()  " << endl 
        << "  " << endl 
        << "clc  " << endl 
        << "clf  " << endl 
        << "close all  " << endl 
        << "  " << endl 
        << "fprintf('\\nLoading of data for the single bacterium\\n')  " << endl 
        << "load X.dat;  " << endl 
        << "load batterio1_c.dat;  " << endl 
        << "batterio1_X=X;  " << endl 
        << "  " << endl 
        << "subplot(2,1,1)  " << endl 
        << "plot(batterio1_X(:,1),batterio1_X(:,2))  " << endl 
        << "hold on  " << endl 
        << "plot(batterio1_X(1,1),batterio1_X(2,1),'g*','LineWidth',4);  " << endl 
        << "plot(batterio1_X(1,floor(end/2)),batterio1_X(2,floor(end/2)),'y*','LineWidth',4);  " << endl 
        << "plot(batterio1_X(1,end),batterio1_X(2,end),'k*','LineWidth',4);  " << endl 
        << "title(['Trajectory bacterium: Green=start;Yellow=middle;Black=end']);  " << endl 
        << "grid on  " << endl 
        << "hold off  " << endl 
        << "  " << endl 
        << "subplot(2,1,2)  " << endl 
        << "plot(batterio1_c(:,1),batterio1_c(:,2)), grid minor  " << endl 
        << "title(['Concentration Ligant along the Trajectory of the bacterium']);  " << endl 
        << "  " << endl 
        << "fprintf('\\nPress a Key to continue ... \\n')  " << endl 
        << "  " << endl 
        << "getkey;  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "close all  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "distribuzione_tempi()  " << endl 
        << "  " << endl 
        << "exit  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Filmatohist.m
    //**************************************************************************************
    
    
    {
        file9 << "function [] = Filmatohist(a,D,mesh_,dt,cont_temp,fig,num_funz,informazioni,Z_max_,car_tecniche)  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "%per cambiare la formattazione della stringa  " << endl 
        << "% formatSpec = '%4.1f\\n';  " << endl 
        << "% str = num2str(100.55,formatSpec)  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "k=1;  " << endl 
        << "phi=60;  " << endl 
        << "theta=90;  " << endl 
        << "fprintf('.....START OF THE ECOLI FILM.....\\n\\n');  " << endl 
        << "  " << endl 
        << "formatSpec = '%4.1f\\n';  " << endl 
        << "  " << endl 
        << "for i=1:length(informazioni)  " << endl 
        << "    fprintf('%s\\n',informazioni{i})  " << endl 
        << "end  " << endl 
        << "    fprintf('\\n\\n')  " << endl 
        << "  " << endl 
        << "T=car_tecniche(1);  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "fprintf('\\nSet view parameter\\n');  " << endl 
        << "phi_s=str2long double(input('\\nFrontal view (in grad): ','s'));  " << endl 
        << "theta_s=str2long double(input('\\nLateral view (in grad): ','s'));  " << endl 
        << "  " << endl 
        << "if ~isnan(phi_s)  " << endl 
        << "    phi=phi_s;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "if ~isnan(theta_s)  " << endl 
        << "    theta=theta_s;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "fprintf('\\nThe time between two fotogram is %f s\\n',car_tecniche(2))  " << endl 
        << "ac=input('\\nPlay faster? y/n: ','s');  " << endl 
        << "  " << endl 
        << "if ac=='y'  " << endl 
        << "    ac=input('\\nMoltiplication factor: ','s');  " << endl 
        << "    if ~isnan(str2long double(ac))   " << endl 
        << "        k=str2long double(ac);  " << endl 
        << "    end  " << endl 
        << "end  " << endl 
        << "fprintf('\\n\\n...........  WE PRESENT ...........\\n\\n')      " << endl 
        << "pause(1);  " << endl 
        << "fprintf('\\n\\n...........  ECOLI FILM!!!  ...........\\n\\n')      " << endl 
        << "figure(fig)  " << endl 
        << "   " << endl 
        << "i=1;  " << endl 
        << "subplot(2,1,1)  " << endl 
        << "        hold off  " << endl 
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl 
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl 
        << "%         contour(X,Y,Nx)  " << endl 
        << "  " << endl 
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl 
        << "        'EdgeColor','none',...  " << endl 
        << "        'FaceLighting','phong')  " << endl 
        << "        camlight left  " << endl 
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl 
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl 
        << "          " << endl 
        << "%         axis equal  " << endl 
        << "          " << endl 
        << "        view([phi theta])  " << endl 
        << "        xlabel('X')  " << endl 
        << "        ylabel('Y')  " << endl 
        << "        zlabel('Density')  " << endl 
        << "        str = num2str((i-1)*dt,formatSpec);  " << endl 
        << "        title(['Density of the population at time T = ',str])  " << endl 
        << "  " << endl 
        << "        hold on  " << endl 
        << "%         quiver(X,Y,DX,DY)  " << endl 
        << "        subplot(2,1,2)  " << endl 
        << "%     end  " << endl 
        << "  " << endl 
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl 
        << "	'EdgeColor','none',...  " << endl 
        << "	'FaceLighting','phong')  " << endl 
        << "    camlight left  " << endl 
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl 
        << "    caxis([0 Z_max_])  " << endl 
        << "%     axis equal  " << endl 
        << "      " << endl 
        << "    view([phi theta])  " << endl 
        << "    xlabel('X')  " << endl 
        << "    ylabel('Y')  " << endl 
        << "    zlabel('Density')  " << endl 
        << "    title(['Density of the population at time T = ',str])  " << endl 
        << "  " << endl 
        << "%input('\\nPress a key to continue : ','s');  " << endl 
        << "fprintf('Press a key to continue ...');  " << endl 
        << "getkey;  " << endl 
        << "figure(fig)  " << endl 
        << "phi_k=phi;  " << endl 
        << "  " << endl 
        << "for i=1:k:cont_temp  " << endl 
        << "  " << endl 
        << "    % Per far 'girare' la ripresa.  " << endl 
        << "      " << endl 
        << "%     phi=phi_k+360/cont_temp*(i-1);  " << endl 
        << "      " << endl 
        << "%     phi=phi+.5*k;  " << endl 
        << "%     theta=theta+1;  " << endl 
        << "      " << endl 
        << "% % %     clc  " << endl 
        << "% % %     fprintf('Press a key to continue ...');  " << endl 
        << "% % % 	input('\\n\\n... ','s');  " << endl 
        << "      " << endl 
        << "      " << endl 
        << "%     if num_funz==1 || num_funz==2 || num_funz==7  " << endl 
        << "        subplot(2,1,1)  " << endl 
        << "        hold off  " << endl 
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl 
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl 
        << "%         contour(X,Y,Nx)  " << endl 
        << "  " << endl 
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl 
        << "        'EdgeColor','none',...  " << endl 
        << "        'FaceLighting','phong')  " << endl 
        << "        camlight left  " << endl 
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl 
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl 
        << "          " << endl 
        << "%         axis equal  " << endl 
        << "          " << endl 
        << "        view([phi theta])  " << endl 
        << "        xlabel('X')  " << endl 
        << "        ylabel('Y')  " << endl 
        << "        zlabel('Density')  " << endl 
        << "        str = num2str((i-1)*dt,formatSpec);  " << endl 
        << "        title(['Density of the population at time T = ',str])  " << endl 
        << "  " << endl 
        << "        hold on  " << endl 
        << "%         quiver(X,Y,DX,DY)  " << endl 
        << "        subplot(2,1,2)  " << endl 
        << "%     end  " << endl 
        << "  " << endl 
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl 
        << "	'EdgeColor','none',...  " << endl 
        << "	'FaceLighting','phong')  " << endl 
        << "    camlight left  " << endl 
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl 
        << "    caxis([0 Z_max_])  " << endl 
        << "%     axis equal  " << endl 
        << "      " << endl 
        << "    view([phi theta])  " << endl 
        << "    xlabel('X')  " << endl 
        << "    ylabel('Y')  " << endl 
        << "    zlabel('Density')  " << endl 
        << "      " << endl 
        << "    title(['Density of the population at time T = ',str])  " << endl 
        << "    pause(.01)  " << endl 
        << "      " << endl 
        << "      " << endl 
        << "      " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "i=cont_temp;  " << endl 
        << "subplot(2,1,1)  " << endl 
        << "        hold off  " << endl 
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl 
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl 
        << "%         contour(X,Y,Nx)  " << endl 
        << "  " << endl 
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl 
        << "        'EdgeColor','none',...  " << endl 
        << "        'FaceLighting','phong')  " << endl 
        << "        camlight left  " << endl 
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl 
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl 
        << "          " << endl 
        << "%         axis equal  " << endl 
        << "          " << endl 
        << "        view([phi theta])  " << endl 
        << "        xlabel('X')  " << endl 
        << "        ylabel('Y')  " << endl 
        << "        zlabel('Density')          " << endl 
        << "        str = num2str(i*dt,formatSpec);  " << endl 
        << "        title(['Density of the population at time T = ',str])  " << endl 
        << "  " << endl 
        << "        hold on  " << endl 
        << "%         quiver(X,Y,DX,DY)  " << endl 
        << "        subplot(2,1,2)  " << endl 
        << "%     end  " << endl 
        << "  " << endl 
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl 
        << "	'EdgeColor','none',...  " << endl 
        << "	'FaceLighting','phong')  " << endl 
        << "    camlight left  " << endl 
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl 
        << "    caxis([0 Z_max_])  " << endl 
        << "%     axis equal  " << endl 
        << "      " << endl 
        << "    view([phi theta])  " << endl 
        << "    xlabel('X')  " << endl 
        << "    ylabel('Y')  " << endl 
        << "    zlabel('Density')      " << endl 
        << "    title(['Density of the population at time T = ',str])  " << endl 
        << "      " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Save_Movie_avi.m
    //**************************************************************************************
    
    
    {
        file10 << "function [] = Save_Movie_avi(a,D,mesh_,dt,cont_temp,fig,num_funz,informazioni,Z_max_,car_tecniche,hd,m)  " << endl 
        << "% Salva il Filmato in formato .avi  " << endl 
        << "  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "        %% RIFINISCO LA GRIGLIA  " << endl 
        << "  " << endl 
        << "fattore_mesh = input('Which step to be applied to the mesh?  ','s');  " << endl 
        << "  " << endl 
        << "if ~isnan(str2long double(fattore_mesh))   " << endl 
        << "    fattore_mesh = str2long double(fattore_mesh);  " << endl 
        << "else  " << endl 
        << "    fattore_mesh=1;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "% fattore_mesh = str2long double(fattore_mesh);  " << endl 
        << "  " << endl 
        << "b_1=mesh_(1):hd(1)*fattore_mesh:mesh_(2);  " << endl 
        << "  " << endl 
        << "if isempty(b_1)  " << endl 
        << "    b_1=linespcae(mesh_(1),mesh_(2),4);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "b_2=mesh_(3):hd(2)*fattore_mesh:mesh_(4);  " << endl 
        << "  " << endl 
        << "if isempty(b_2)  " << endl 
        << "    b_2=linespcae(mesh_(3),mesh_(4),4);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "k=1;  " << endl 
        << "phi=60;  " << endl 
        << "theta=90;  " << endl 
        << "fprintf('.....START FILM.....\\n\\n');  " << endl 
        << "  " << endl 
        << "formatSpec = '%4.1f\\n';  " << endl 
        << "  " << endl 
        << "for i=1:length(informazioni)  " << endl 
        << "    fprintf('%s\\n',informazioni{i})  " << endl 
        << "end  " << endl 
        << "    fprintf('\\n\\n')  " << endl 
        << "  " << endl 
        << "T=car_tecniche(1);  " << endl 
        << "  " << endl 
        << "fprintf('\\nSet view parameter\\n');  " << endl 
        << "phi_s=str2long double(input('\\nFrontal view (in grad): ','s'));  " << endl 
        << "theta_s=str2long double(input('\\nLateral view (in grad): ','s'));  " << endl 
        << "  " << endl 
        << "if ~isnan(phi_s) || ~isnan(theta_s)  " << endl 
        << "    phi=phi_s;  " << endl 
        << "    theta=theta_s;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "fprintf('\\nThe time between two fotogram is %f s\\n',car_tecniche(2))  " << endl 
        << "ac=input('\\nPlay faster? y/n: ','s');  " << endl 
        << "  " << endl 
        << "if ac=='y'  " << endl 
        << "ac=input('\\nMoltiplication factor: ','s');  " << endl 
        << "if ~isnan(str2long double(ac))   " << endl 
        << "k=str2long double(ac);  " << endl 
        << "end  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "ac=input('\\nSet max Z: ','s');  " << endl 
        << "  " << endl 
        << "if ~isnan(str2long double(ac))   " << endl 
        << "    Z_max_ = str2long double(ac);  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "fprintf('\\n\\n........... CINE-ECOLI!!!  ...........\\n\\n')     " << endl 
        << "  " << endl 
        << "scrsz = get(0,'ScreenSize');  " << endl 
        << "  " << endl 
        << "figure('Position', [scrsz(3) scrsz(4) scrsz(3)/2 scrsz(4)/2])   " << endl 
        << "figura_=gcf;  " << endl 
        << "  " << endl 
        << "nome = sprintf('EColi-sim-%03d', m);"<<endl
        << "writerObj = VideoWriter(nome);  " << endl 
        << "open(writerObj);  " << endl 
        << "  " << endl 
        << "phi_k=phi;  " << endl 
        << "  " << endl 
        << "for i=1:k:cont_temp  " << endl 
        << "      " << endl 
//        << "    phi=phi_k+360/cont_temp*(i-1);  " << endl 
        << "      " << endl 
        << "%     if num_funz==1 || num_funz==2 || num_funz==7  " << endl 
        << "        subplot(2,1,1)  " << endl 
        << "        hold off  " << endl 
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl 
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl 
        << "%         contour(X,Y,Nx)  " << endl 
        << "  " << endl 
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl 
        << "        'EdgeColor','none',...  " << endl 
        << "        'FaceLighting','phong')  " << endl 
        << "        camlight left  " << endl 
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl 
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 10])  " << endl 
        << "          " << endl 
        << "%         axis equal  " << endl 
        << "          " << endl 
        << "        view([phi theta])  " << endl 
        << "        xlabel('X')  " << endl 
        << "        ylabel('Y')  " << endl 
        << "        zlabel('Density')  " << endl 
        << "        str = num2str(i*dt,formatSpec);  " << endl 
        << "        title(['Density of the population at time T = ',str])  " << endl 
        << "        hold on  " << endl 
        << "          " << endl 
        << "%         quiver(X,Y,DX,DY)  " << endl 
        << "        subplot(2,1,2)  " << endl 
        << "%     end  " << endl 
        << "%     interp2(X,xx,yy)  " << endl 
        << "  " << endl 
        << "%     [xi,yi]=meshgrid(b_1,b_2);  " << endl 
        << "%     H=interp2(a{1,1},a{1,2},D{1,i}',xi,yi);  " << endl 
        << "%       " << endl 
        << "%    surf(b_1,b_2,H,'FaceColor','interp',...  " << endl 
        << "% 	'EdgeColor','none',...  " << endl 
        << "% 	'FaceLighting','phong')  " << endl 
        << "      " << endl 
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl 
        << "	'EdgeColor','none',...  " << endl 
        << "	'FaceLighting','phong')  " << endl 
        << "  " << endl 
        << "    camlight left  " << endl 
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl 
        << "    caxis([0 Z_max_])  " << endl 
        << "      " << endl 
        << "%     axis equal  " << endl 
        << "      " << endl 
        << "    view([phi theta])  " << endl 
        << "    xlabel('X')  " << endl 
        << "    ylabel('Y')  " << endl 
        << "    zlabel('Density')  " << endl 
        << "    str = num2str(i*dt,formatSpec);  " << endl 
        << "	title(['Density of the population at time T = ',str])  " << endl 
        << "  " << endl 
        << "	frame = getframe(figura_);  " << endl 
        << "    writeVideo(writerObj,frame);  " << endl 
        << "      " << endl 
        << "    pause(.1)  " << endl 
        << "      " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "close(writerObj);  " << endl 
        << "  " << endl 
        << "fprintf('Press a key to continue ...');  " << endl 
        << "input('\\n\\n... ','s');  " << endl 
        << "close all  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // function_c.m
    //**************************************************************************************
    
    
    {
        file11 << "function c=function_c(x,t,T,num_funz)  " << endl 
        << "% function of the the chemical substance  " << endl 
        << "if nargin==0  " << endl 
        << "    num_funz=1;  " << endl 
        << "    T=100;  " << endl 
        << "    t=0;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "%% Funzione c(.,.)  " << endl 
        << "  " << endl 
        << "switch num_funz  " << endl 
        << "      " << endl 
        << "    case 1  " << endl 
        << "        %% SOMBRERO ONDEGGIANTE  " << endl 
        << "        T=T/2;  " << endl 
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl 
        << "        c = 1+6*abs((1+(t-1)/T).*sin(R+2*(t-1)/T)./(R+2*(t-1)/T));  " << endl 
        << "      " << endl 
        << "      " << endl 
        << "    case 2  " << endl 
        << "        %% GAUSSIAN  " << endl 
        << "        sigma=100;  " << endl 
        << "          " << endl 
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl 
        << "        c = 1+6*exp(-R.^2/sigma);  " << endl 
        << "      " << endl 
        << "    case 3      " << endl 
        << "  " << endl 
        << "  " << endl 
        << "     c=1+(t<=T)*0+3*(t>T)*(t<=T+1)*(t-T)^2+3*(t>T+1);  " << endl 
        << "         " << endl 
        << "    case 4  " << endl 
        << "        %% CONST>>DECRESCE  " << endl 
        << "        c=1+(t<=T)+(t>T)*(t<=T+1)*(t-T-1)^2+(t>T+1)*0;  " << endl 
        << "          " << endl 
        << "    case 5  " << endl 
        << "        %% SUPP COMPATTO GAUSSIANA  " << endl 
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl 
        << "        c = 1+2*exp(-R.^2/10).*(abs(R)<=5);  " << endl 
        << "      " << endl 
        << "    case 6  " << endl 
        << "        %% CONST>> CRESC. DECRESC.  " << endl 
        << "        T=2*T;  " << endl 
        << "        c=1+(t<T/3)*0+(t>=T/3)*(t<2*T/3)+(t>2*T/3)*0;  " << endl 
        << "          " << endl 
        << "    case 7  " << endl 
        << "        sigma=5;  " << endl 
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl 
        << "        c = 1 + 3*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl 
        << "          " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // MovieCpp2matlab.m
    //**************************************************************************************
    
    
    {
        file12 << "function MovieCpp2matlab(n,m)  " << endl 
        << "  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "%% Caricamento Dati  " << endl 
        << "  " << endl 
        << "fprintf('---------- CINE-ECOLI-----------\\n\\n')  " << endl 
        << "  " << endl 
        << " " << endl        
        << "    nome = sprintf('Call_Matlab%d-sim-%03d.txt', n,m);" << endl
        << "    Call_Matlab = importdata(nome);" << endl 
        << "    fprintf('\\nLoading') " << endl 
        << "    X = Call_Matlab.textdata{1}; " << endl 
        << "    X=load(X);  " << endl 
        << "    indice = Call_Matlab.textdata{2}; " << endl 
        << "    indice=load(indice); " << endl 
        << "    fprintf('\\n\\nLoading files terminato ... \\n\\n') " << endl 
        << "    carat_tecniche = Call_Matlab.data; " << endl 
        << "pause(1)  " << endl 
        << "clc  " << endl 
        << "  " << endl 
        << "%% Visualizzazione informazioni relative alla Simulazione  " << endl 
        << "  " << endl 
        << "fprintf('----------- CINE-ECOLI -------------\\n\\n')  " << endl 
        << "      " << endl 
        << " informazioni = Call_Matlab.textdata; " << endl 
        << "  " << endl 
        << "    for i=1:length(informazioni)  " << endl 
        << "        fprintf('%s\\n',informazioni{i})  " << endl 
        << "    end  " << endl 
        << "          " << endl 
        << "    fprintf('\\n\\n')  " << endl 
        << "  " << endl 
        << "	fprintf('Press a key to continue ...');  " << endl 
        << "    getkey;  " << endl 
        << "      " << endl 
        << "    clc  " << endl 
        << "%    fprintf('--------- RUBERESTI MAI UNA AUTO? -----------\\n\\n')  " << endl 
        << "%    fprintf('\\n\\n       ...Loading Film...\\n\\n')  " << endl 
        << "%    fprintf('\\n\\n--------- NON COMPRARE DVD PIRATA, ARRRGH --------\\n\\n')  " << endl 
        << "      " << endl 
        << "    num_funz = carat_tecniche(3) ;  " << endl 
        << "      " << endl 
        << "    if isnan(num_funz)  " << endl 
        << "        num_funz=8;  " << endl 
        << "    end  " << endl 
        << "  " << endl 
        << "    %% Caricamento vettore posizione   " << endl 
        << "      " << endl 
        << "    P=zeros(2,length(indice)-2,indice(2));  " << endl 
        << "  " << endl
        << " n_index=0" << endl
        << "    for i=1:(length(indice)-2)  " << endl 
        << "          " << endl 
        << "        P(1,i,:)=X(n_index+1:i*indice(2),1);  " << endl
        << "        P(2,i,:)=X(n_index+1:i*indice(2),2);  " << endl
        << "        n_index = i*indice(2);" << endl
        << "    end  " << endl 
        << "      " << endl 
        << "    %% Max asse Z histogramma  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "    %%  ASSI REGOLATI IN BASE AL MASSIMO ASSOLUTO SIMILE A axis equi  " << endl 
        << "    mesh_=[min(min(min(P(:,:,:))))-.1,max(max(max(P(:,:,:))))+.1,min(min(min(P(:,:,:))))-.1,max(max(max(P(:,:,:))))+.1];  " << endl 
        << "    divx=floor(sqrt(length(indice)-2));  " << endl 
        << "    divy=floor(sqrt(length(indice)-2));  " << endl 
        << "  " << endl 
        << "    hd=[(mesh_(2)-mesh_(1))/divx (mesh_(2)-mesh_(1))/divy];  " << endl 
        << "  " << endl 
        << "    %% CARICAMENTO FILMATO  " << endl 
        << "      " << endl 
        << "    fig=1;  " << endl 
        << "    [D,a,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd,mesh_,indice(2)...  " << endl 
        << "        -indice(1));  " << endl 
        << "      " << endl 
        << "    fprintf('Max Z Global = %f',Z_max_)  " << endl 
        << "    fprintf('\\nMax Z at the end of the simulation: Z(T_f) = %f',Z_max_fin)  " << endl 
        << "    fprintf('\\nNow Z is set as Z(max)  = 40')          " << endl 
        << "    ac=input('\\nSet Z max: ','s');  " << endl 
        << "  " << endl 
        << "    if ~isnan(str2long double(ac))   " << endl 
        << "        Z_max_ = str2long double(ac);  " << endl 
        << "    else  " << endl 
        << "        Z_max_ = 40;  " << endl 
        << "    end  " << endl 
        << "    close all  " << endl 
        << "    clc  " << endl 
        << "      " << endl 
        << "    Filmatohist(a,D,mesh_,carat_tecniche(2),indice(2),...  " << endl 
        << "        fig,num_funz,informazioni,Z_max_, carat_tecniche);  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "    %% VO AVANTI  " << endl 
        << "  " << endl 
        << "    fprintf('----------------------------------------\\n\\n')  " << endl 
        << "  " << endl 
        << "    clc  " << endl 
        << "      " << endl 
        << "    fprintf('Press a key to continue ...');  " << endl 
        << "    input('\\n\\n... ','s');  " << endl 
        << "    close all  " << endl 
        << "      " << endl 
        << "    clc  " << endl 
        << "      " << endl 
        << "    reply = input('Replay the Film with a different mesh and/or view ?  y/n: ','s');  " << endl 
        << "    close all  " << endl 
        << "      " << endl 
        << "    %% REPLICHE 2  " << endl 
        << "      " << endl 
        << "    while(reply=='y')  " << endl 
        << "          " << endl 
        << "        clc  " << endl 
        << "        fattore_mesh = input('Which step to be applied to the mesh?  ','s');  " << endl 
        << "      " << endl 
        << "         %% RIFINISCO LA GRIGLIA  " << endl 
        << "        if ~isnan(str2long double(fattore_mesh))   " << endl 
        << "            fattore_mesh = str2long double(fattore_mesh);  " << endl 
        << "        else  " << endl 
        << "            fattore_mesh=1;  " << endl 
        << "        end  " << endl 
        << "          " << endl 
        << "        [D,a,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd*fattore_mesh,mesh_,indice(2)-indice(1));  " << endl 
        << "      " << endl 
        << "        fprintf('Max Z Global = %f',Z_max_)  " << endl 
        << "        fprintf('\\nMax Z at the end of the simulation: Z(T_f) = %f',Z_max_fin)  " << endl 
        << "        fprintf('\\nNow Z is set as Z(max)  = 40')          " << endl 
        << "        ac=input('\\nSet Z max: ','s');  " << endl 
        << "  " << endl 
        << "          " << endl 
        << "  " << endl 
        << "  " << endl 
        << "        if ~isnan(str2long double(ac))   " << endl 
        << "            Z_max_ = str2long double(ac);  " << endl 
        << "        else  " << endl 
        << "            Z_max_ = 40;  " << endl 
        << "        end  " << endl 
        << "        close all  " << endl 
        << "        clc  " << endl 
        << "        Filmatohist(a,D,mesh_,carat_tecniche(2),indice(2),fig,num_funz,informazioni,Z_max_, carat_tecniche);  " << endl 
        << "        clc  " << endl 
        << "        fprintf('Press a key to continue ...');  " << endl 
        << "        input('\\n\\n... ','s');  " << endl 
        << "        close all  " << endl 
        << "        clc   " << endl 
        << "        reply = input('Replay the Film with a different mesh and/or view ?  y/n: ','s');  " << endl 
        << "           " << endl 
        << "    end      " << endl 
        << "      " << endl 
        << "    clc  " << endl 
        << "    reply = input('Save the film in .avi format?  y/n: ','s');  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "    if reply=='y'  " << endl 
        << "  " << endl 
        << "        Save_Movie_avi(a,D,mesh_,carat_tecniche(2),indice(2),fig,...  " << endl 
        << "                num_funz,informazioni,Z_max_,carat_tecniche,hd,m)     " << endl 
        << "    end  " << endl 
        << "      " << endl 
        << "    clc  " << endl 
        << "      " << endl 
        << "    Evolution_Mass_center(P,indice(2))  " << endl 
        << "      " << endl 
        << "    fprintf('Press a key to continue ...');  " << endl 
        << "    getkey;  " << endl 
        << "      " << endl 
        << "    close;  " << endl 
        << "    clc  " << endl 
        << "          " << endl 
        << "    %% SALVATAGGIO DATI C++  " << endl 
        << "      " << endl 
        << "    reply = input('Save data of the c++ program y/n: ','s');  " << endl 
        << "  " << endl 
        << "    if (reply=='y')  " << endl 
        << "  " << endl 
        << "        clear b_1 b_2 ans salvataggio_ reply hd i j reply P X Y Nx DX DY   " << endl 
        << "        clear mesh1_ D Z_max_ a divx divy fig mesh_ no_conc num_funz  " << endl 
        << "        clear T ans n num_tra salvataggio_ t fattore_mesh dt  " << endl 
        << "        clear C_T C_T_media M M_C salti ac Z_max_fin  " << endl 
        << "        clear delta_C_media lambda_path sciopero rif_temp theta_T  " << endl 
        << "        clear MsupC_T MsupdeltaC MsupJump Msuplambda MsupP Msuptheta  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "        ora_salvataggio=round(clock);  " << endl 
        << "        fprintf('\\nSAVING DATA\\n')  " << endl 
        << "        matFilename = sprintf('Cpp_SDE_STEV_Data_%d_%d_%d_ore%dh%dm.mat',ora_salvataggio(1),ora_salvataggio(2),ora_salvataggio(3),ora_salvataggio(4),ora_salvataggio(5));  " << endl 
        << "        clear ora_salvataggio  " << endl 
        << "        save(matFilename);  " << endl 
        << "          " << endl 
        << "%        delete('/Users/stefanobelloni/Documents/MATLAB/CTRW_Model_Memory/SDE_Towards_Realism_1.8/*.txt');  " << endl 
        << "  " << endl 
        << "          " << endl 
        << "    end  " << endl 
        << "  " << endl 
        << "      " << endl 
        << "distribuzione_tempi(3,n,m); " << endl 
        << "distribuzione_tempi(4,n,m);  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "clc  " << endl 
        << "clf  " << endl 
        << "close all  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // distribuzione_tempi.m
    //**************************************************************************************
    
    
    {
        file13 << "function distribuzione_tempi(n_file,n,cont_sim) " << endl 
        << "  " << endl 
        << "% Il programma elabora le statischire riguardanti i tempi di salto  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "fprintf('\\nCaricamento dati relativi ai salti ... \\n')  " << endl 
        << "nome = sprintf('Call_Matlab%d-sim-%03d.txt', n,cont_sim);" << endl
        << "Call_Matlab = importdata(nome); " << endl 
        << "tau=Call_Matlab.textdata{n_file}; " << endl 
        << "tau=load(tau);  " << endl 
        << "if (n_file==4)"
        << "x_max=1.2;" << endl
        << "else" << endl
        << "x_max=6;" << endl
        << "end " << endl
        << "x=0:.01:2*x_max;  " << endl
        << "  " << endl 
        << "  " << endl 
        << "R=tau(:,2);  " << endl 
        << "n=length(R);  " << endl 
        << "  " << endl 
        << "figure(1)  " << endl 
        << "  " << endl 
        << "hist(R,sqrt(n))  " << endl 
        << "xlim([0 x_max]) " << endl
        << "fprintf('\\nPress a key to continue ... \\n')  " << endl 
        << "  " << endl 
        << "getkey;  " << endl 
        << "  " << endl 
        << "  " << endl 
        << "beta=mean(R);  " << endl 
        << "clc  " << endl 
        << "fprintf('The measured mean: %f', beta); " << endl 
        << "fprintf('\\nThe measured variance: %f', var(R)); " << endl 
        << "fprintf('\\nThe std: %f\\n\\n', std(R)); " << endl 
        << "  " << endl 
        << "fprintf('\\nCreation matrix and elaboration ... \\n')  " << endl 
        << "  " << endl 
//        << "f_exp = makedist('Exponential','mu',beta);  " << endl 
//        << "R_exp=random(f_exp,n,1);  " << endl 
//        << "  " << endl 
//        << "A_E=zeros(length(x),1);  " << endl 
//        << "  " << endl 
//        << "for i=1:length(x)  " << endl 
//        << "A_E(i)=sum(R_exp>x(i));  " << endl 
//        << "end  " << endl 
//        << "  " << endl 
//        << "  " << endl 
        << "A=zeros(length(x),1);  " << endl 
        << "  " << endl 
        << "for i=1:length(x)  " << endl 
        << "A(i)=sum(R>x(i));  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "clc  " << endl 
        << "fprintf('The measured mean: %f', beta); " << endl 
        << "fprintf('\\nThe measured variance: %f', var(R)); " << endl 
        << "fprintf('\\nThe std: %f\\n\\n', std(R)); " << endl 
        << "  " << endl 
        << "figure(2)  " << endl 
        << "  " << endl 
        << "plot(x,A/n,x,exp(-x/beta)); set(gca,'yscale','log')  " << endl
        << "xlim([0 x_max]) " << endl
        << "legend('Simulated','Exponential')  " << endl 
        << "xlabel('run lengths')  " << endl 
        << "ylabel('Fraction of runs of a given length')  " << endl 
        << "  " << endl 
        << "fprintf('\\nPress a key to continue ... \\n')  " << endl 
        << "  " << endl 
        << "getkey;  " << endl 
        << "  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // getkey.m
    //**************************************************************************************
    
    
    {
        file14 << "function ch = getkey(m)   " << endl 
        << "  " << endl 
        << "% GETKEY - get a single keypress  " << endl 
        << "%   CH = GETKEY waits for a keypress and returns the ASCII code. Accepts  " << endl 
        << "%   all ascii characters, including backspace (8), space (32), enter (13),  " << endl 
        << "%   etc, that can be typed on the keyboard. Non-ascii keys (ctrl, alt, ..)  " << endl 
        << "%   return a NaN. CH is a long double.   " << endl 
        << "%  " << endl 
        << "%   CH = GETKEY('non-ascii') uses non-documented matlab features to return  " << endl 
        << "%   a string describing the key pressed. In this way keys like ctrl, alt,  " << endl 
        << "%   tab etc. can also distinguished. CH is a string.  " << endl 
        << "%  " << endl 
        << "%   This function is kind of a workaround for getch in C. It uses a modal,  " << endl 
        << "%   but non-visible window, which does show up in the taskbar.  " << endl 
        << "%   C-language keywords: KBHIT, KEYPRESS, GETKEY, GETCH  " << endl 
        << "%  " << endl 
        << "%   Examples:  " << endl 
        << "%  " << endl 
        << "%    fprintf('\\nPress any key: ') ;  " << endl 
        << "%    ch = getkey ;  " << endl 
        << "%    fprintf('%c\\n',ch) ;  " << endl 
        << "%  " << endl 
        << "%    fprintf('\\nPress the Ctrl-key: ') ;  " << endl 
        << "%    if strcmp(getkey('non-ascii'),'control'),  " << endl 
        << "%      fprintf('OK\\n') ;  " << endl 
        << "%    else  " << endl 
        << "%      fprintf(' ... wrong key ...\\n') ;  " << endl 
        << "%    end  " << endl 
        << "%  " << endl 
        << "%  See also INPUT, UIWAIT  " << endl 
        << "%           GETKEYWAIT (File Exchange)  " << endl 
        << "  " << endl 
        << "% for Matlab 6.5 and higher  " << endl 
        << "% version 1.3 (jan 2012)  " << endl 
        << "% author : Jos van der Geest  " << endl 
        << "% email  : jos@jasen.nl  " << endl 
        << "%  " << endl 
        << "% History  " << endl 
        << "% 2005 - creation  " << endl 
        << "% dec 2006 - modified lay-out and help  " << endl 
        << "% apr 2009 - tested for more recent MatLab releases   " << endl 
        << "% jan 2012 - modified a few properties, included check is figure still  " << endl 
        << "%            exists (after comment on FEX by Andrew).  " << endl 
        << "  " << endl 
        << "% Determine the callback string to use  " << endl 
        << "if nargin == 1,  " << endl 
        << "    if strcmpi(m,'non-ascii'),  " << endl 
        << "        callstr = 'set(gcbf,''Userdata'',get(gcbf,''Currentkey'')) ; uiresume ' ;  " << endl 
        << "    else         " << endl 
        << "        error('Argument should be the string ''non-ascii''') ;  " << endl 
        << "    end  " << endl 
        << "else  " << endl 
        << "    callstr = 'set(gcbf,''Userdata'',long double(get(gcbf,''Currentcharacter''))) ; uiresume ' ;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "% Set up the figure  " << endl 
        << "% May be the position property  should be individually tweaked to avoid visibility  " << endl 
        << "fh = figure(...  " << endl 
        << "    'name','Press a key', ...  " << endl 
        << "    'keypressfcn',callstr, ...  " << endl 
        << "    'windowstyle','modal',...   " << endl 
        << "    'numbertitle','off', ...  " << endl 
        << "    'position',[0 0  1 1],...  " << endl 
        << "    'userdata','timeout') ;   " << endl 
        << "try  " << endl 
        << "    % Wait for something to happen  " << endl 
        << "    uiwait ;  " << endl 
        << "    ch = get(fh,'Userdata') ;  " << endl 
        << "    if isempty(ch),  " << endl 
        << "        ch = NaN ;   " << endl 
        << "    end  " << endl 
        << "catch  " << endl 
        << "    % Something went wrong, return and empty matrix.  " << endl 
        << "    ch = [] ;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << "if ishandle(fh)  " << endl 
        << "    delete(fh) ;  " << endl 
        << "end  " << endl 
        << "  " << endl 
        << " " << endl 
        << " " << endl; 
    }
    
    
    //**************************************************************************************
    
    
  
    
}



/**
 * This function write the .m files for automatic inputs. If you want to add a new .m files.
 * To add new functions you might use the program mintocpp.cpp which do the conversion that you can paste here.
 */

void Scrittura_m_filesAutomatic(){
    
    ofstream file1("Caricamento_filmato_hist.m");
    ofstream file2("Movie_Matlab_from_cpp.m");
    ofstream file3("functionC.m");
    ofstream file4("hist3.m");
    ofstream file5("Evolution_Mass_center.m");
    ofstream file6("Movie_Matlab_from_cpp_and_single.m");
    ofstream file7("functionC1.m");
    ofstream file8("traiettorie_singole.m");
    ofstream file9("Filmatohist.m");
    ofstream file10("Save_Movie_avi.m");
    ofstream file11("function_c.m");
    ofstream file12("MovieCpp2matlab.m");
    ofstream file13("distribuzione_tempi.m");
    ofstream file14("getkey.m");
    //**************************************************************************************
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Caricamento_filmato_hist.m
    //**************************************************************************************
    
    
    {
        file1 << "function [D,b,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd,mesh_,r)  " << endl
        << "a=cell(1,2);  " << endl
        << "D=cell(1,r);  " << endl
        << "% % % a{1,1}=round(mesh_(1)):round(hd):round(mesh_(2));  " << endl
        << "% % % a{1,2}=round(mesh_(3)):round(hd):round(mesh_(4));  " << endl
        << "clc  " << endl
        << "fprintf('\\n\\n     --------- LOADING FILM!!! --------\\n\\n')  " << endl
        << "  " << endl
        << "%fprintf('--------- RUBERESTI MAI UN'AUTO? -----------\\n\\n')  " << endl
        << "%fprintf('\\n\\n       ...Caricamento Filmato...\\n\\n')  " << endl
        << "%fprintf('\\n\\n--------- NON COMPRARE DVD PIRATA, ARRRGH --------\\n\\n')  " << endl
        << "tic  " << endl
        << "a{1,1}=mesh_(1):hd(1):mesh_(2);  " << endl
        << "  " << endl
        << "if isempty(a{1,1})  " << endl
        << "    a{1,1}=linspace(mesh_(1),mesh_(2),4);  " << endl
        << "end  " << endl
        << "  " << endl
        << "a{1,2}=mesh_(3):hd(2):mesh_(4);  " << endl
        << "  " << endl
        << "if isempty(a{1,2})  " << endl
        << "    a{1,2}=linspace(mesh_(3),mesh_(4),4);  " << endl
        << "end  " << endl
        << "  " << endl
        << "% Z_max_=3;  " << endl
        << "  " << endl
        << "max_Z_temp=zeros(r,1);  " << endl
        << "  " << endl
        << "for i=1:r  " << endl
        << "    [N,b]=hist3(P(:,:,i)','Edges',a);  " << endl
        << "	D{1,i}=N;  " << endl
        << "    max_Z_temp(i)=max(max(N));  " << endl
        << "end  " << endl
        << "  " << endl
        << "fprintf('\\n\\n     --------- END LOADING FILM!!! --------\\n\\n')  " << endl
//        << "pause(1)  " << endl
//        << "clc  " << endl
        << "  " << endl
        << "% Z_max_=max(max(N));  " << endl
        << "Z_max_fin =max(max(N));  " << endl
        << "Z_max_=max(max_Z_temp)+1;  " << endl
        << "  " << endl
        << "scrsz = get(0,'ScreenSize');  " << endl
        << "figure('Position', [scrsz(3) scrsz(4) scrsz(3)/3 scrsz(4)/3])  " << endl
        << "plot(1:r,max_Z_temp)  " << endl
        << "axis([0 r 0 Z_max_])  " << endl
        << "grid on  " << endl
//        << "% input('\\nPress a key to continue : ','s');  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Movie_Matlab_from_cpp.m
    //**************************************************************************************
    
    {
        file2 << "function [] = Movie_Matlab_from_cpp()  " << endl
        << "%UNTITLED Summary of this function goes here  " << endl
        << "%   Detailed explanation goes here  " << endl
        << "  " << endl
        << "n=load('file_matlab.txt');" << endl
        << "m=n(2)-n(1)" << endl
        << "for i=0:n(1)-1" << endl
        << "    m=m+1;" << endl
        << "    MovieCpp2matlab(i,m)  " << endl
        << "end" << endl
        << "exit;  " << endl
        << "%fprintf('\\ntype exit to quit ... \\n');  " << endl
        << "  " << endl
        << "end  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // functionC.m
    //**************************************************************************************
    
    
    {
        file3 << "function [c,x,y] = functionC(M,t,T,num_funz)  " << endl
        << "n_mesh_punt=80;  " << endl
        << "[x,y]=meshgrid(linspace(M(1),M(2),n_mesh_punt),linspace(M(3),M(4),n_mesh_punt));  " << endl
        << "  " << endl
        << "switch num_funz  " << endl
        << "      " << endl
        << "    case 0  " << endl
        << "         " << endl
        << "        sigma=10;  " << endl
        << "          " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "        c = 1+6*exp(-R.^2/sigma);  " << endl
        << "         " << endl
        << "    case 1 " << endl
        << "         " << endl
        << "        T=15;         " << endl
        << "        c=1+1.*(0*x.*y)+2*(t>T); " << endl
        << "     " << endl
        << "    case 2  " << endl
        << " " << endl
        << "          " << endl
        << "        T=100;  " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "        c = 1+(R<8).*1.2.*abs((1+(t)/T).*sin(2*pi*(R+2*(t)/T)/2)./(R+(t)/T))...  " << endl
        << "            +.8*(R>=8).*(R<16).*abs(cos(atan(sin(R)+t/T)))...  " << endl
        << "            +(R>=16).*.1.*abs((1+(t)/T).*cos(sqrt(abs(y))).*atan((x.^2)).*sin(R+1.1*pi*((t)/T)));  " << endl
        << "      " << endl
        << "    case 3  " << endl
        << " " << endl
        << "        c= 1.*(0*x.*y)+ 1+2*(t<=6)+7*(t>6)*(t<=6+1)*pow(t-6,2)+7*(t>6+1); " << endl
        << "         " << endl
        << "    case 4  " << endl
        << "         " << endl
        << "        c= 1.*(0*x.*y)+ 1+7*(t<8)+(t>=15)*(t<25)+3*(t>25); " << endl
        << "          " << endl
        << "    case 5  " << endl
        << "         " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps; " << endl
        << "        c = 3*(1+max(R,x)/2); " << endl
        << "      " << endl
        << "    case 6  " << endl
        << "         " << endl
        << "        c= 18.2*exp(10*x); " << endl
        << "                  " << endl
        << "	case 7  " << endl
        << "         " << endl
        << "        c = 0*x+18.2*exp(0.2*t); " << endl
        << "        " << endl
        << "    otherwise " << endl
        << "         " << endl
        << "        c=1+0.*x; " << endl
        << " " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // hist3.m
    //**************************************************************************************
    
    
    {
        file4 << "function [nn,ctrs] = hist3(varargin)  " << endl
        << "%HIST3 Three-dimensional histogram of bivariate data.  " << endl
        << "%   HIST3(X) bins the elements of the M-by-2 matrix X into a 10-by-10 grid  " << endl
        << "%   of equally-spaced containers, and plots a histogram.  Each column of X  " << endl
        << "%   corresponds to one dimension in the bin grid.  " << endl
        << "%  " << endl
        << "%   HIST3(X,NBINS) plots a histogram using an NBINS(1)-by-NBINS(2) grid of  " << endl
        << "%   bins.  HIST3(X,'Nbins',NBINS) is equivalent to HIST3(X,NBINS).  " << endl
        << "%  " << endl
        << "%   HIST3(X,CTRS), where CTRS is a two-element cell array of numeric  " << endl
        << "%   vectors with monotonically non-decreasing values, uses a 2D grid of  " << endl
        << "%   bins centered on CTRS{1} in the first dimension and on CTRS{2} in the  " << endl
        << "%   second.  HIST3 assigns rows of X falling outside the range of that grid  " << endl
        << "%   to the bins along the outer edges of the grid, and ignores rows of X  " << endl
        << "%   containing NaNs.  HIST3(X,'Ctrs',CTRS) is equivalent to HIST3(X,CTRS).  " << endl
        << "%  " << endl
        << "%   HIST3(X,'Edges',EDGES), where EDGES is a two-element cell array  " << endl
        << "%   of numeric vectors with monotonically non-decreasing values, uses a 2D  " << endl
        << "%   grid of bins with edges at EDGES{1} in the first dimension and at  " << endl
        << "%   EDGES{2} in the second.  The (i,j)-th bin includes the value X(k,:) if  " << endl
        << "%  " << endl
        << "%      EDGES{1}(i) <= X(k,1) < EDGES{1}(i+1) and  " << endl
        << "%      EDGES{2}(j) <= X(k,2) < EDGES{2}(j+1).  " << endl
        << "%  " << endl
        << "%   Rows of X that that fall on the upper edges of the grid, EDGES{1}(end)  " << endl
        << "%   or EDGES{2}(end), are counted in the (I,j)-th or (i,J)-th bins, where  " << endl
        << "%   I and J are the lengths of EDGES{1} and EDGES{2}.  HIST3 does not count  " << endl
        << "%   rows of X falling outside the range of the grid.  Use -Inf and Inf in  " << endl
        << "%   EDGES to include all non-NaN values.  " << endl
        << "%  " << endl
        << "%   N = HIST3(X,...) returns a matrix containing the number of elements of  " << endl
        << "%   X that fall in each bin of the grid, and does not plot the histogram.  " << endl
        << "%     " << endl
        << "%   [N,C] = HIST3(X,...) returns the positions of the bin centers in a  " << endl
        << "%   1-by-2 cell array of numeric vectors, and does not plot the histogram.  " << endl
        << "%  " << endl
        << "%   HIST3(AX,X,...) plots into AX instead of GCA.  " << endl
        << "%  " << endl
        << "%   HIST3(..., 'PARAM1',val1, 'PARAM2',val2, ...) allows you to specify  " << endl
        << "%   graphics parameter name/value pairs to fine-tune the plot.  " << endl
        << "%  " << endl
        << "%   Examples:  " << endl
        << "%  " << endl
        << "%      % Create the car data and make a histogram on a 7x7 grid of bins.  " << endl
        << "%      load carbig  " << endl
        << "%      X = [MPG,Weight];  " << endl
        << "%      hist3(X,[7 7]);  " << endl
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl
        << "%  " << endl
        << "%      % Make a histogram with semi-transparent bars  " << endl
        << "%      hist3(X,[7 7],'FaceAlpha',.65);  " << endl
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl
        << "%      set(gcf,'renderer','opengl');  " << endl
        << "%  " << endl
        << "%      % Make a histogram with bars colored according to height  " << endl
        << "%      hist3(X,[7 7]);  " << endl
        << "%      xlabel('MPG'); ylabel('Weight');  " << endl
        << "%      set(gcf,'renderer','opengl');  " << endl
        << "%      set(get(gca,'child'),'FaceColor','interp','CDataMode','auto');  " << endl
        << "%  " << endl
        << "%      % Specify bin centers, different in each direction.  Get back  " << endl
        << "%      % counts, but don't make the plot.  " << endl
        << "%      cnt = hist3(X, {0:10:50 2000:500:5000});  " << endl
        << "%  " << endl
        << "%   See also ACCUMARRAY, BAR, BAR3, HIST, HISTC.  " << endl
        << "  " << endl
        << "%   Copyright 1993-2009 The MathWorks, Inc.  " << endl
        << "%   $Revision: 1.1.8.3 $  $Date: 2011/05/09 01:25:19 $  " << endl
        << "  " << endl
        << "[cax,args,nargs] = axescheck(varargin{:});  " << endl
        << "  " << endl
        << "if nargs < 1  " << endl
        << "    error(message('stats:hist3:TooFewInputs'))  " << endl
        << "end  " << endl
        << "x = args{1};  " << endl
        << "   " << endl
        << "% See if nbins/ctrs was given as the second argument, or only name/value  " << endl
        << "% pairs.  " << endl
        << "if nargs > 1 && ~ischar(args{2})  " << endl
        << "    binSpec = args{2};  " << endl
        << "    args = args(3:end); % strip off x and nbins/ctrs  " << endl
        << "else  " << endl
        << "    binSpec = [];  " << endl
        << "    args = args(2:end); % strip off x  " << endl
        << "end  " << endl
        << "  " << endl
        << "% Process input parameter name/value pairs, assume unrecognized ones are  " << endl
        << "% graphics properties.  " << endl
        << "pnames = {'nbins','ctrs','edges'};  " << endl
        << "dflts =  { [],     [],       []};  " << endl
        << "[nbins,ctrs,edges,~,plotArgs] = internal.stats.parseArgs(pnames,dflts,args{:});  " << endl
        << "  " << endl
        << "% Make sure they haven't mixed 'nbins'/'ctrs'/'edges' name/value pairs with  " << endl
        << "% the CTRS or NBINS unnamed second arg syntax, or used more than one of  " << endl
        << "% those parameter name/value pairs.  " << endl
        << "if (isempty(nbins)+isempty(ctrs)+isempty(edges)+isempty(binSpec)) < 3  " << endl
        << "    error(message('stats:hist3:AmbiguousBinSpec'));  " << endl
        << "elseif ~isempty(binSpec)  " << endl
        << "    if iscell(binSpec)  % hist3(x,ctrs)  " << endl
        << "        ctrs = binSpec;  " << endl
        << "    else                % hist3(x,nbins)  " << endl
        << "        nbins = binSpec;  " << endl
        << "    end  " << endl
        << "end  " << endl
        << "  " << endl
        << "if ~isempty(nbins)  " << endl
        << "    % Use the specified number of bars in each direction, centers and edges  " << endl
        << "    % to be determined.  " << endl
        << "    histBehavior = true;  " << endl
        << "    if ~(isnumeric(nbins) && numel(nbins)==2)  " << endl
        << "        error(message('stats:hist3:BadNbins'));  " << endl
        << "    end  " << endl
        << "    autobins = true;  " << endl
        << "      " << endl
        << "elseif ~isempty(ctrs)  " << endl
        << "    % Use the specified bin centers.  " << endl
        << "    histBehavior = true;  " << endl
        << "    if ~(iscell(ctrs) && numel(ctrs)==2 && isnumeric(ctrs{1}) && isnumeric(ctrs{2}))  " << endl
        << "        error(message('stats:hist3:BadCtrs'));  " << endl
        << "    end  " << endl
        << "    ctrs = {ctrs{1}(:)' ctrs{2}(:)'};  " << endl
        << "    autobins = false;  " << endl
        << "    nbins = [length(ctrs{1}) length(ctrs{2})];  " << endl
        << "      " << endl
        << "elseif ~isempty(edges)  " << endl
        << "    % Use the specified bin edges.  " << endl
        << "    histBehavior = false;  " << endl
        << "    if ~(iscell(edges) && numel(edges)==2 && isnumeric(edges{1}) && isnumeric(edges{2}))  " << endl
        << "        error(message('stats:hist3:BadEdges'));  " << endl
        << "    end  " << endl
        << "    edges = {edges{1}(:)' edges{2}(:)'};  " << endl
        << "    autobins = false;  " << endl
        << "    % Just as with histc, there will be #edges bins  " << endl
        << "    nbins = [length(edges{1}) length(edges{2})];  " << endl
        << "      " << endl
        << "else  " << endl
        << "    % Assume a 10x10 grid of bars, centers and edges to be determined.  " << endl
        << "    histBehavior = true;  " << endl
        << "    autobins = true;  " << endl
        << "    nbins = [10 10];  " << endl
        << "end  " << endl
        << "  " << endl
        << "[nrows,ncols] = size(x);  " << endl
        << "if ncols ~= 2  " << endl
        << "    error(message('stats:hist3:WrongNumCols'));  " << endl
        << "end  " << endl
        << "  " << endl
        << "% Special case for empty data (follows what HIST does).  " << endl
        << "if isempty(x)  " << endl
        << "    if autobins  " << endl
        << "       ctrs = {1:nbins(1) 1:nbins(2)};  " << endl
        << "    end  " << endl
        << "    n = zeros(nbins); % Nothing to count, return nbins(1) by nbins(2) zeros  " << endl
        << "      " << endl
        << "else  " << endl
        << "    % Bin each observation in the x-direction, and in the y-direction.  " << endl
        << "    bin = zeros(nrows,2);  " << endl
        << "    for i = 1:2  " << endl
        << "        minx = min(x(:,i));  " << endl
        << "        maxx = max(x(:,i));  " << endl
        << "          " << endl
        << "        % If only the number of bins was given, compute edges and centers  " << endl
        << "        % for equal-sized bins spanning the data.  " << endl
        << "        if autobins  " << endl
        << "            if isinf(minx) || isinf(maxx)  " << endl
        << "                error(message('stats:hist3:InfData'));  " << endl
        << "            elseif minx == maxx  " << endl
        << "                minx = minx - floor(nbins(i)/2) - 0.5;  " << endl
        << "                maxx = maxx + ceil(nbins(i)/2) - 0.5;  " << endl
        << "            end  " << endl
        << "            binwidth{i} = (maxx - minx) / nbins(i);  " << endl
        << "            edges{i} = minx + binwidth{i}*(0:nbins(i));  " << endl
        << "            ctrs{i} = edges{i}(1:nbins(i)) + binwidth{i}/2;  " << endl
        << "            % Make histc mimic hist behavior:  everything < ctrs(1) gets  " << endl
        << "            % counted in first bin, everything > ctrs(end) gets counted in  " << endl
        << "            % last bin.  ctrs, edges, and binwidth do not reflect that, but  " << endl
        << "            % histcEdges does.  " << endl
        << "            histcEdges = [-Inf edges{i}(2:end-1) Inf];  " << endl
        << "              " << endl
        << "        % If the bin centers were given, compute their edges and widths.  " << endl
        << "        elseif histBehavior  " << endl
        << "            c = ctrs{i};  " << endl
        << "            dc = diff(c);  " << endl
        << "            edges{i} = [c(1) c] + [-dc(1) dc dc(end)]/2;  " << endl
        << "            binwidth{i} = diff(edges{i});  " << endl
        << "            % Make histc mimic hist behavior:  everything < ctrs(1) gets  " << endl
        << "            % counted in first bin, everything > ctrs(end) gets counted in  " << endl
        << "            % last bin.  ctrs, edges, and binwidth do not reflect that, but  " << endl
        << "            % histcEdges does.  " << endl
        << "            histcEdges = [-Inf edges{i}(2:end-1) Inf];  " << endl
        << "              " << endl
        << "        % If the bin edges were given, compute their widths and centers (if  " << endl
        << "        % asked for).  " << endl
        << "        else % if ~histBehavior  " << endl
        << "            e = edges{i};  " << endl
        << "            de = diff(e);  " << endl
        << "            histcEdges = e;  " << endl
        << "            % Make the display mimic bar's histc behavior: an implied bin  " << endl
        << "            % above edges(end), the same width as the last explicit one.  " << endl
        << "            % ctrs, edges, and binwidth need that explicitly, histcEdges  " << endl
        << "            % doesn't.  " << endl
        << "            edges{i} = [e e(end)+de(end)];  " << endl
        << "            binwidth{i} = [de de(end)];  " << endl
        << "            if nargout > 1  " << endl
        << "                c = zeros(size(de));  " << endl
        << "                c(1) = e(1) + de(1)/2;  " << endl
        << "                for j = 2:length(c)  " << endl
        << "                    c(j) = 2*e(j) - c(j-1);  " << endl
        << "                end  " << endl
        << "                % When edges are specified, it may not be possible to return  " << endl
        << "                % centers for which the edges are midpoints.  Warn if that's  " << endl
        << "                % the case.  " << endl
        << "                if any(c <= e(1:end-1)) || ...  " << endl
        << "                   abs(c(end) - (e(end)-de(end)/2)) > 1000*eps(de(end));  " << endl
        << "                    warning(message('stats:hist3:InconsistentEdges'));  " << endl
        << "                    c = e(1:end-1) + de/2;  " << endl
        << "                end  " << endl
        << "                ctrs{i} = [c e(end)+de(end)/2];  " << endl
        << "            end  " << endl
        << "        end  " << endl
        << "          " << endl
        << "        % Get the 1D bin numbers for this column of x.  Make sure +Inf  " << endl
        << "        % goes into the nth bin, not the (n+1)th.  " << endl
        << "        [dum,bin(:,i)] = histc(x(:,i),histcEdges,1);  " << endl
        << "        bin(:,i) = min(bin(:,i),nbins(i));  " << endl
        << "    end  " << endl
        << "      " << endl
        << "    % Combine the two vectors of 1D bin counts into a grid of 2D bin  " << endl
        << "    % counts.  " << endl
        << "    n = accumarray(bin(all(bin>0,2),:),1,nbins);  " << endl
        << "end  " << endl
        << "  " << endl
        << "if 0 < nargout  " << endl
        << "    nn = n;  " << endl
        << "    return  " << endl
        << "end  " << endl
        << "  " << endl
        << "del = .001; % space between bars, relative to bar size  " << endl
        << "  " << endl
        << "% Build x-coords for the eight corners of each bar.  " << endl
        << "xx = edges{1};  " << endl
        << "xx = [xx(1:nbins(1))+del*binwidth{1}; xx(2:nbins(1)+1)-del*binwidth{1}];  " << endl
        << "xx = [reshape(repmat(xx(:)',2,1),4,nbins(1)); NaN(1,nbins(1))];  " << endl
        << "xx = [repmat(xx(:),1,4) NaN(5*nbins(1),1)];  " << endl
        << "xx = repmat(xx,1,nbins(2));  " << endl
        << "  " << endl
        << "% Build y-coords for the eight corners of each bar.  " << endl
        << "yy = edges{2};  " << endl
        << "yy = [yy(1:nbins(2))+del*binwidth{2}; yy(2:nbins(2)+1)-del*binwidth{2}];  " << endl
        << "yy = [reshape(repmat(yy(:)',2,1),4,nbins(2)); NaN(1,nbins(2))];  " << endl
        << "yy = [repmat(yy(:),1,4) NaN(5*nbins(2),1)];  " << endl
        << "yy = repmat(yy',nbins(1),1);  " << endl
        << "  " << endl
        << "% Build z-coords for the eight corners of each bar.  " << endl
        << "zz = zeros(5*nbins(1), 5*nbins(2));  " << endl
        << "zz(5*(1:nbins(1))-3, 5*(1:nbins(2))-3) = n;  " << endl
        << "zz(5*(1:nbins(1))-3, 5*(1:nbins(2))-2) = n;  " << endl
        << "zz(5*(1:nbins(1))-2, 5*(1:nbins(2))-3) = n;  " << endl
        << "zz(5*(1:nbins(1))-2, 5*(1:nbins(2))-2) = n;  " << endl
        << "  " << endl
        << "cax = newplot(cax);  " << endl
        << "holdState = ishold(cax);  " << endl
        << "  " << endl
        << "% Plot the bars in a light steel blue.  " << endl
        << "cc = repmat(cat(3,.75,.85,.95), [size(zz) 1]);  " << endl
        << "  " << endl
        << "% Plot the surface, using any specified graphics properties to override  " << endl
        << "% defaults.  " << endl
        << "h = surf(cax, xx, yy, zz, cc, 'tag','hist3', plotArgs{:});  " << endl
        << "  " << endl
        << "if ~holdState  " << endl
        << "    % Set ticks for each bar if fewer than 16 and the centers/edges are  " << endl
        << "    % integers.  Otherwise, leave the default ticks alone.  " << endl
        << "    if (nbins(1)<16)  " << endl
        << "        if histBehavior && all(floor(ctrs{1})==ctrs{1})  " << endl
        << "            set(cax,'xtick',ctrs{1});  " << endl
        << "        elseif ~histBehavior && all(floor(edges{1})==edges{1})  " << endl
        << "            set(cax,'xtick',edges{1});  " << endl
        << "        end  " << endl
        << "    end  " << endl
        << "    if (nbins(2)<16)  " << endl
        << "        if histBehavior && all(floor(ctrs{2})==ctrs{2})  " << endl
        << "            set(cax,'ytick',ctrs{2});  " << endl
        << "        elseif ~histBehavior && all(floor(edges{2})==edges{2})  " << endl
        << "            set(cax,'ytick',edges{2});  " << endl
        << "        end  " << endl
        << "    end  " << endl
        << "      " << endl
        << "    % Set the axis limits to have some space at the edges of the bars.  " << endl
        << "    dx = range(edges{1})*.05;  " << endl
        << "    dy = range(edges{2})*.05;  " << endl
        << "    set(cax,'xlim',[edges{1}(1)-dx edges{1}(end)+dx]);  " << endl
        << "    set(cax,'ylim',[edges{2}(1)-dy edges{2}(end)+dy]);  " << endl
        << "      " << endl
        << "    view(cax,3);  " << endl
        << "    grid(cax,'on');  " << endl
        << "    set(get(cax,'parent'),'renderer','zbuffer');  " << endl
        << "end  " << endl
        << "  " << endl
        << "if nargout > 0  " << endl
        << "    nn = n;  " << endl
        << "end  " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Evolution_Mass_center.m
    //**************************************************************************************
    
    
    {
        file5 << "function [] = Evolution_Mass_center(P,dim_P_Temp)  " << endl
        << "%EVOLUTION_MASS_CENTER Summary of this function goes here  " << endl
        << "%   Detailed explanation goes here  " << endl
        << "  " << endl
        << "    P_mean=zeros(2,dim_P_Temp);  " << endl
        << "      " << endl
        << "    for i=1:dim_P_Temp  " << endl
        << "        P_mean(1,i)=mean(P(1,:,i));  " << endl
        << "        P_mean(2,i)=mean(P(2,:,i));  " << endl
        << "    end  " << endl
        << "  " << endl
        << "    MsupP=[min(P_mean(1,:))-.02 max(P_mean(1,:))+.02 min(P_mean(2,:))-.02 max(P_mean(2,:))+.02];  " << endl
        << "      " << endl
        << "    plot(P_mean(1,:),P_mean(2,:));  " << endl
        << "    axis(MsupP)  " << endl
        << "    hold on  " << endl
        << "    plot(P_mean(1,1),P_mean(2,1),'g*','LineWidth',4);  " << endl
        << "    plot(P_mean(1,floor(end/2)),P_mean(2,floor(end/2)),'y*','LineWidth',4);  " << endl
        << "    plot(P_mean(1,end),P_mean(2,end),'k*','LineWidth',4);  " << endl
        << "    title(['Trajectory center of mass of the population: Green=start;Yellow=middle;Black=end']);  " << endl
        << "    grid on  " << endl
        << "    hold off  " << endl
        << "  " << endl
        << "end  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Movie_Matlab_from_cpp_and_single.m
    //**************************************************************************************
    
    
    {
        file6 << "function [] = Movie_Matlab_from_cpp_and_single()  " << endl
        << "%UNTITLED Summary of this function goes here  " << endl
        << "%   Detailed explanation goes here  " << endl
        << "  " << endl
        << "  " << endl
        << "MovieCpp2matlab;  " << endl
        << "exit;  " << endl
        << "%fprintf('\\ntype exit to quit ... \\n');  " << endl
        << "  " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // functionC1.m
    //**************************************************************************************
    
    
    {
        file7 << "function [c,x,y] = functionC1(X_x,M,t,T,num_funz)  " << endl
        << "n_mesh_punt=200;  " << endl
        << "[x,y]=meshgrid(X_x,linspace(M(3),M(4),n_mesh_punt));  " << endl
        << "  " << endl
        << "switch num_funz  " << endl
        << "      " << endl
        << "    case 1  " << endl
        << "        %% SOMBRERO ONDEGGIANTE  " << endl
        << "% % %         T=T/3;  " << endl
        << "  " << endl
        << "% % %         T=100;  " << endl
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "% % %         c = 1+6*abs((1+(t)/T).*sin((R+2*(t)/T)/2)./(R+(t)/T));  " << endl
        << "          " << endl
        << "        T=30;  " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "        c = 1+(R<8).*1.2.*abs((1+(t)/T).*sin(2*pi*(R+2*(t)/T)/2)./(R+(t)/T))...  " << endl
        << "            +.8*(R>=8).*(R<16).*abs(cos(atan(sin(R)+t/T)))...  " << endl
        << "            +(R>=16).*.1.*abs((1+(t)/T).*cos(sqrt(abs(y))).*atan((x.^2)).*sin(R+1.1*pi*((t)/T)));  " << endl
        << "  " << endl
        << "% % %         T=400;  " << endl
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "% % %         c = pi+(1+atan(cos(R.^2))).*sin(R+8*(t-1)/T);  " << endl
        << "  " << endl
        << "  " << endl
        << "% % %         T=600;  " << endl
        << "% % %         T=T/3;  " << endl
        << "% % %         R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "% % %         if t<=T/2  " << endl
        << "% % %             c = 1+6*abs((1+(t-1)/(5*T)).*sin(R+2*(t-1)/(5*T))./(R+2*(t-1)/(5*T)));  " << endl
        << "% % %         else  " << endl
        << "% % %             c = 1+5*exp(-(t-T/2)/T)*6*abs((1+(t-1)/(5*T)).*sin(R+2*(t-1)/(5*T))./(R+2*(t-1)/(5*T)));  " << endl
        << "% % %         end  " << endl
        << "          " << endl
        << "% % %         T=600;  " << endl
        << "% % %         T=T/3;  " << endl
        << "% % % 	      R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "% % %         c = 1+(1+abs(tan(R))).*exp(T-t).*abs((1+(t-1)/T).*sin(R+2*(t-1)/T)./(R+2*(t-1)/T));  " << endl
        << "  " << endl
        << "          " << endl
        << "% % %         %% VIDEO GLOBALE  " << endl
        << "% % %         mesh_=47.1163;  " << endl
        << "% % %         [X1,Y] = meshgrid(-mesh_:.1:mesh_);  " << endl
        << "% % %         R = sqrt(X1.^2 + Y.^2) + eps;  " << endl
        << "% % %         c =5*abs((1+(t-1)/T)*sin(R+(t-1)/T)./(R+(t-1)/T));  " << endl
        << "% % %         contour(X1,Y,c)  " << endl
        << "      " << endl
        << "    case 2  " << endl
        << "        %% GAUSSIAN  " << endl
        << "        sigma=100;  " << endl
        << "          " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "        c = 1+2*exp(-R.^2/sigma);  " << endl
        << "      " << endl
        << "    case 3  " << endl
        << "        T=T/3;  " << endl
        << "        %% CONST >> CRESCE  " << endl
        << "%      c = 0*sqrt(x.^2 + 1)*exp(-y.^2/(t+1));  " << endl
        << "%      c=exp(-t/80)*abs(.1*x+t/10*sin(y));  " << endl
        << "%      c=abs(.1*x+t/(T)*sin(y));  " << endl
        << "%     c=abs(.1*x+3*sin(R)-(.1*x+(t-50)/10*sin(y)));  " << endl
        << "%     c=abs(.1*x+3*sin(R)-(.1*x+(t-30)/10*sin(R)));  " << endl
        << "%      c=(t>=5)*abs(5*(1+(t-1)/100)*sin(R+(t-1)/100)./(R+(t-1)/100))+...  " << endl
        << "%          (t<5)*0*x;  " << endl
        << "%      c=(t<=5)*0*sin(R)+(t>5)*(3+0*sin(R+(t-1)/100));  " << endl
        << "%      c =3+zeros(1,dim_cell/2);  " << endl
        << "  " << endl
        << "     c=1.*(0*x.*y)+(t<=T)*0+(t>T)*(t<=T+1)*(t-T)^2+(t>T+1);  " << endl
        << "         " << endl
        << "    case 4  " << endl
        << "        %% CONST>>DECRESCE  " << endl
        << "        c=1.*(0*x.*y)+(t<=T)+(t>T)*(t<=T+1)*(t-T-1)^2+(t>T+1)*0;  " << endl
        << "          " << endl
        << "    case 5  " << endl
        << "        %% SUPP COMPATTO GAUSSIANA  " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "        c = 1+2*exp(-R.^2/10).*(abs(R)<=5);  " << endl
        << "      " << endl
        << "    case 6  " << endl
        << "        %% CONST>> CRESC. DECRESC.  " << endl
        << "        c=1.*(0*x.*y)+(t<T/3)*0+(t>=T/3)*(t<2*T/3)+(t>2*T/3)*0;  " << endl
        << "                  " << endl
        << "	case 7  " << endl
        << "        sigma=5;  " << endl
        << "        R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "%         c = 1 + 3*exp(-R.^2/100).*(R<=20)+.5246*exp(-(R-40).^2/100).*(R>20)+.5*(R>20);  " << endl
        << "%         c = 1 + 3*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl
        << "        T=200;c = 1 + (sin(4*pi*t/T)+1).*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl
        << "      " << endl
        << "    case 8  " << endl
        << "          " << endl
        << "        if (t<=T/5)  " << endl
        << "                num_funz=1;  " << endl
        << "                [c,x,y]=functionC(M,5*t,T,num_funz);  " << endl
        << "        end  " << endl
        << "          " << endl
        << "        if (t<=2*T/5 && t>T/5)  " << endl
        << "                num_funz=6;  " << endl
        << "                [c,x,y]=functionC(M,5*(t-T/5),T,num_funz);  " << endl
        << "        end  " << endl
        << "          " << endl
        << "        if (t<=3*T/5 && t>2*T/5)   " << endl
        << "                num_funz=7;  " << endl
        << "                [c,x,y]=functionC(M,5*(t-2*T/5),T,num_funz);  " << endl
        << "        end  " << endl
        << "          " << endl
        << "        if (t<=4*T/5 && t>3*T/5)   " << endl
        << "                num_funz=2;  " << endl
        << "                [c,x,y]=functionC(M,5*(t-3*T/5),T,num_funz);  " << endl
        << "        end  " << endl
        << "          " << endl
        << "        if (t>4*T/5)   " << endl
        << "                num_funz=1;  " << endl
        << "                [c,x,y]=functionC(M,5*(t-4*T/5),T,num_funz);  " << endl
        << "        end  " << endl
        << "  " << endl
        << "    otherwise  " << endl
        << "        c=0.*x;  " << endl
        << "%         sigma=5;  " << endl
        << "%         R = sqrt(x.^2 + y.^2) + eps;  " << endl
        << "%         T=200;c = 1 + (sin(4*pi*t/T)+1).*exp(-R.^2/sigma).*(R<=5)+atan(x).*sin(3*pi*t/T)*(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // traiettorie_singole.m
    //**************************************************************************************
    
    
    {
        file8 << "function [] = traiettorie_singole()  " << endl
        << "  " << endl
        << "clc  " << endl
        << "clf  " << endl
        << "close all  " << endl
        << "  " << endl
        << "fprintf('\\nLoading of data for the single bacterium\\n')  " << endl
        << "load X.dat;  " << endl
        << "load batterio1_c.dat;  " << endl
        << "batterio1_X=X;  " << endl
        << "  " << endl
        << "subplot(2,1,1)  " << endl
        << "plot(batterio1_X(:,1),batterio1_X(:,2))  " << endl
        << "hold on  " << endl
        << "plot(batterio1_X(1,1),batterio1_X(2,1),'g*','LineWidth',4);  " << endl
        << "plot(batterio1_X(1,floor(end/2)),batterio1_X(2,floor(end/2)),'y*','LineWidth',4);  " << endl
        << "plot(batterio1_X(1,end),batterio1_X(2,end),'k*','LineWidth',4);  " << endl
        << "title(['Trajectory bacterium: Green=start;Yellow=middle;Black=end']);  " << endl
        << "grid on  " << endl
        << "hold off  " << endl
        << "  " << endl
        << "subplot(2,1,2)  " << endl
        << "plot(batterio1_c(:,1),batterio1_c(:,2)), grid minor  " << endl
        << "title(['Concentration Ligant along the Trajectory of the bacterium']);  " << endl
        << "  " << endl
        << "fprintf('\\nPress a Key to continue ... \\n')  " << endl
        << "  " << endl
//        << "getkey;  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << "close all  " << endl
        << "clc  " << endl
        << "  " << endl
        << "distribuzione_tempi()  " << endl
        << "  " << endl
        << "exit  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Filmatohist.m
    //**************************************************************************************
    
    
    {
        file9 << "function [] = Filmatohist(a,D,mesh_,dt,cont_temp,fig,num_funz,informazioni,Z_max_,car_tecniche)  " << endl
        << "clc  " << endl
        << "  " << endl
        << "%per cambiare la formattazione della stringa  " << endl
        << "% formatSpec = '%4.1f\\n';  " << endl
        << "% str = num2str(100.55,formatSpec)  " << endl
        << "  " << endl
        << "  " << endl
        << "k=1;  " << endl
        << "phi=60;  " << endl
        << "theta=90;  " << endl
        << "fprintf('.....START OF THE ECOLI FILM.....\\n\\n');  " << endl
        << "  " << endl
        << "formatSpec = '%4.1f\\n';  " << endl
        << "  " << endl
        << "for i=1:length(informazioni)  " << endl
        << "    fprintf('%s\\n',informazioni{i})  " << endl
        << "end  " << endl
        << "    fprintf('\\n\\n')  " << endl
        << "  " << endl
        << "T=car_tecniche(1);  " << endl
        << "  " << endl
        << "  " << endl
        << "fprintf('\\nSet view parameter\\n');  " << endl
//        << "phi_s=str2long double(input('\\nFrontal view (in grad): ','s'));  " << endl
//        << "theta_s=str2long double(input('\\nLateral view (in grad): ','s'));  " << endl
        << "  " << endl
//        << "if ~isnan(phi_s)  " << endl
//        << "    phi=phi_s;  " << endl
//        << "end  " << endl
        << "  " << endl
//        << "if ~isnan(theta_s)  " << endl
//        << "    theta=theta_s;  " << endl
//        << "end  " << endl
        << "  " << endl
        << "  " << endl
//        << "fprintf('\\nThe time between two fotogram is %f s\\n',car_tecniche(2))  " << endl
//        << "ac=input('\\nPlay faster? y/n: ','s');  " << endl
        << "  " << endl
//        << "if ac=='y'  " << endl
//        << "    ac=input('\\nMoltiplication factor: ','s');  " << endl
//        << "    if ~isnan(str2long double(ac))   " << endl
//        << "        k=str2long double(ac);  " << endl
//        << "    end  " << endl
//        << "end  " << endl
        << "fprintf('\\n\\n...........  WE PRESENT ...........\\n\\n')      " << endl
//        << "pause(1);  " << endl
        << "fprintf('\\n\\n...........  ECOLI FILM!!!  ...........\\n\\n')      " << endl
        << "figure(fig)  " << endl
        << "   " << endl
        << "i=1;  " << endl
        << "subplot(2,1,1)  " << endl
        << "        hold off  " << endl
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl
        << "%         contour(X,Y,Nx)  " << endl
        << "  " << endl
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl
        << "        'EdgeColor','none',...  " << endl
        << "        'FaceLighting','phong')  " << endl
        << "        camlight left  " << endl
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl
        << "          " << endl
        << "%         axis equal  " << endl
        << "          " << endl
        << "        view([phi theta])  " << endl
        << "        xlabel('X')  " << endl
        << "        ylabel('Y')  " << endl
        << "        zlabel('Density')  " << endl
        << "        str = num2str((i-1)*dt,formatSpec);  " << endl
        << "        title(['Density of the population at time T = ',str])  " << endl
        << "  " << endl
        << "        hold on  " << endl
        << "%         quiver(X,Y,DX,DY)  " << endl
        << "        subplot(2,1,2)  " << endl
        << "%     end  " << endl
        << "  " << endl
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl
        << "	'EdgeColor','none',...  " << endl
        << "	'FaceLighting','phong')  " << endl
        << "    camlight left  " << endl
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl
        << "    caxis([0 Z_max_])  " << endl
        << "%     axis equal  " << endl
        << "      " << endl
        << "    view([phi theta])  " << endl
        << "    xlabel('X')  " << endl
        << "    ylabel('Y')  " << endl
        << "    zlabel('Density')  " << endl
        << "    title(['Density of the population at time T = ',str])  " << endl
        << "  " << endl
//        << "%input('\\nPress a key to continue : ','s');  " << endl
//        << "fprintf('Press a key to continue ...');  " << endl
//        << "getkey;  " << endl
        << "figure(fig)  " << endl
        << "phi_k=phi;  " << endl
        << "  " << endl
        << "for i=1:k:cont_temp  " << endl
        << "  " << endl
        << "    % Per far 'girare' la ripresa.  " << endl
        << "      " << endl
        << "%     phi=phi_k+360/cont_temp*(i-1);  " << endl
        << "      " << endl
        << "%     phi=phi+.5*k;  " << endl
        << "%     theta=theta+1;  " << endl
        << "      " << endl
        << "% % %     clc  " << endl
        << "% % %     fprintf('Press a key to continue ...');  " << endl
        << "% % % 	input('\\n\\n... ','s');  " << endl
        << "      " << endl
        << "      " << endl
        << "%     if num_funz==1 || num_funz==2 || num_funz==7  " << endl
        << "        subplot(2,1,1)  " << endl
        << "        hold off  " << endl
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl
        << "%         contour(X,Y,Nx)  " << endl
        << "  " << endl
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl
        << "        'EdgeColor','none',...  " << endl
        << "        'FaceLighting','phong')  " << endl
        << "        camlight left  " << endl
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl
        << "          " << endl
        << "%         axis equal  " << endl
        << "          " << endl
        << "        view([phi theta])  " << endl
        << "        xlabel('X')  " << endl
        << "        ylabel('Y')  " << endl
        << "        zlabel('Density')  " << endl
        << "        str = num2str((i-1)*dt,formatSpec);  " << endl
        << "        title(['Density of the population at time T = ',str])  " << endl
        << "  " << endl
        << "        hold on  " << endl
        << "%         quiver(X,Y,DX,DY)  " << endl
        << "        subplot(2,1,2)  " << endl
        << "%     end  " << endl
        << "  " << endl
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl
        << "	'EdgeColor','none',...  " << endl
        << "	'FaceLighting','phong')  " << endl
        << "    camlight left  " << endl
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl
        << "    caxis([0 Z_max_])  " << endl
        << "%     axis equal  " << endl
        << "      " << endl
        << "    view([phi theta])  " << endl
        << "    xlabel('X')  " << endl
        << "    ylabel('Y')  " << endl
        << "    zlabel('Density')  " << endl
        << "      " << endl
        << "    title(['Density of the population at time T = ',str])  " << endl
        << "    pause(.01)  " << endl
        << "      " << endl
        << "      " << endl
        << "      " << endl
        << "end  " << endl
        << "  " << endl
        << "i=cont_temp;  " << endl
        << "subplot(2,1,1)  " << endl
        << "        hold off  " << endl
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl
        << "%         contour(X,Y,Nx)  " << endl
        << "  " << endl
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl
        << "        'EdgeColor','none',...  " << endl
        << "        'FaceLighting','phong')  " << endl
        << "        camlight left  " << endl
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 8])  " << endl
        << "          " << endl
        << "%         axis equal  " << endl
        << "          " << endl
        << "        view([phi theta])  " << endl
        << "        xlabel('X')  " << endl
        << "        ylabel('Y')  " << endl
        << "        zlabel('Density')          " << endl
        << "        str = num2str(i*dt,formatSpec);  " << endl
        << "        title(['Density of the population at time T = ',str])  " << endl
        << "  " << endl
        << "        hold on  " << endl
        << "%         quiver(X,Y,DX,DY)  " << endl
        << "        subplot(2,1,2)  " << endl
        << "%     end  " << endl
        << "  " << endl
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl
        << "	'EdgeColor','none',...  " << endl
        << "	'FaceLighting','phong')  " << endl
        << "    camlight left  " << endl
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl
        << "    caxis([0 Z_max_])  " << endl
        << "%     axis equal  " << endl
        << "      " << endl
        << "    view([phi theta])  " << endl
        << "    xlabel('X')  " << endl
        << "    ylabel('Y')  " << endl
        << "    zlabel('Density')      " << endl
        << "    title(['Density of the population at time T = ',str])  " << endl
        << "      " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // Save_Movie_avi.m
    //**************************************************************************************
    
    
    {
        file10 << "function [] = Save_Movie_avi(a,D,mesh_,dt,cont_temp,fig,num_funz,informazioni,Z_max_,car_tecniche,hd,m)  " << endl
        << "% Salva il Filmato in formato .avi  " << endl
        << "  " << endl
        << "clc  " << endl
        << "  " << endl
        << "        %% RIFINISCO LA GRIGLIA  " << endl
        << "  " << endl
//        << "fattore_mesh = input('Which step to be applied to the mesh?  ','s');  " << endl
        << "  " << endl
//        << "if ~isnan(str2long double(fattore_mesh))   " << endl
//        << "    fattore_mesh = str2long double(fattore_mesh);  " << endl
//        << "else  " << endl
        << "    fattore_mesh=1;  " << endl
//        << "end  " << endl
        << "  " << endl
        << "% fattore_mesh = str2long double(fattore_mesh);  " << endl
        << "  " << endl
        << "b_1=mesh_(1):hd(1)*fattore_mesh:mesh_(2);  " << endl
        << "  " << endl
        << "if isempty(b_1)  " << endl
        << "    b_1=linespcae(mesh_(1),mesh_(2),4);  " << endl
        << "end  " << endl
        << "  " << endl
        << "b_2=mesh_(3):hd(2)*fattore_mesh:mesh_(4);  " << endl
        << "  " << endl
        << "if isempty(b_2)  " << endl
        << "    b_2=linespcae(mesh_(3),mesh_(4),4);  " << endl
        << "end  " << endl
        << "  " << endl
        << "k=1;  " << endl
        << "phi=60;  " << endl
        << "theta=90;  " << endl
        << "fprintf('.....START FILM.....\\n\\n');  " << endl
        << "  " << endl
        << "formatSpec = '%4.1f\\n';  " << endl
        << "  " << endl
        << "for i=1:length(informazioni)  " << endl
        << "    fprintf('%s\\n',informazioni{i})  " << endl
        << "end  " << endl
        << "    fprintf('\\n\\n')  " << endl
        << "  " << endl
        << "T=car_tecniche(1);  " << endl
        << "  " << endl
        << "fprintf('\\nSet view parameter\\n');  " << endl
//        << "phi_s=str2long double(input('\\nFrontal view (in grad): ','s'));  " << endl
//        << "theta_s=str2long double(input('\\nLateral view (in grad): ','s'));  " << endl
//        << "  " << endl
//        << "if ~isnan(phi_s) || ~isnan(theta_s)  " << endl
//        << "    phi=phi_s;  " << endl
//        << "    theta=theta_s;  " << endl
//        << "end  " << endl
//        << "  " << endl
//        << "fprintf('\\nThe time between two fotogram is %f s\\n',car_tecniche(2))  " << endl
//        << "ac=input('\\nPlay faster? y/n: ','s');  " << endl
//        << "  " << endl
//        << "if ac=='y'  " << endl
//        << "ac=input('\\nMoltiplication factor: ','s');  " << endl
//        << "if ~isnan(str2long double(ac))   " << endl
//        << "k=str2long double(ac);  " << endl
//        << "end  " << endl
//        << "end  " << endl
//        << "  " << endl
//        << "ac=input('\\nSet max Z: ','s');  " << endl
        << "  " << endl
//        << "if ~isnan(str2long double(ac))   " << endl
//        << "    Z_max_ = str2long double(ac);  " << endl
//        << "end  " << endl
        << "  " << endl
        << "fprintf('\\n\\n........... CINE-ECOLI!!!  ...........\\n\\n')     " << endl
        << "  " << endl
        << "scrsz = get(0,'ScreenSize');  " << endl
        << "  " << endl
        << "figure('Position', [scrsz(3) scrsz(4) scrsz(3)/2 scrsz(4)/2])   " << endl
        << "figura_=gcf;  " << endl
        << "  " << endl
        << "nome = sprintf('EColi-sim-%03d', m);"<<endl
        << "writerObj = VideoWriter(nome);  " << endl
        << "open(writerObj);  " << endl
        << "  " << endl
        << "phi_k=phi;  " << endl
        << "  " << endl
        << "for i=1:k:cont_temp  " << endl
        << "      " << endl
        //        << "    phi=phi_k+360/cont_temp*(i-1);  " << endl
        << "      " << endl
        << "%     if num_funz==1 || num_funz==2 || num_funz==7  " << endl
        << "        subplot(2,1,1)  " << endl
        << "        hold off  " << endl
        << "        [Nx,X,Y]=functionC(mesh_,i*dt,T,num_funz);  " << endl
        << "%         [DX,DY] = gradient(Nx,.2,.2);  " << endl
        << "%         contour(X,Y,Nx)  " << endl
        << "  " << endl
        << "        surf(X,Y,Nx,'FaceColor','interp',...  " << endl
        << "        'EdgeColor','none',...  " << endl
        << "        'FaceLighting','phong')  " << endl
        << "        camlight left  " << endl
        << "        axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 5])  " << endl
        << "%         axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 10])  " << endl
        << "          " << endl
        << "%         axis equal  " << endl
        << "          " << endl
        << "        view([phi theta])  " << endl
        << "        xlabel('X')  " << endl
        << "        ylabel('Y')  " << endl
        << "        zlabel('Density')  " << endl
        << "        str = num2str(i*dt,formatSpec);  " << endl
        << "        title(['Density of the population at time T = ',str])  " << endl
        << "        hold on  " << endl
        << "          " << endl
        << "%         quiver(X,Y,DX,DY)  " << endl
        << "        subplot(2,1,2)  " << endl
        << "%     end  " << endl
        << "%     interp2(X,xx,yy)  " << endl
        << "  " << endl
        << "%     [xi,yi]=meshgrid(b_1,b_2);  " << endl
        << "%     H=interp2(a{1,1},a{1,2},D{1,i}',xi,yi);  " << endl
        << "%       " << endl
        << "%    surf(b_1,b_2,H,'FaceColor','interp',...  " << endl
        << "% 	'EdgeColor','none',...  " << endl
        << "% 	'FaceLighting','phong')  " << endl
        << "      " << endl
        << "    surf(a{1,1},a{1,2},D{1,i}','FaceColor','interp',...  " << endl
        << "	'EdgeColor','none',...  " << endl
        << "	'FaceLighting','phong')  " << endl
        << "  " << endl
        << "    camlight left  " << endl
        << "    axis([mesh_(1) mesh_(2) mesh_(3) mesh_(4) 0 Z_max_])  " << endl
        << "    caxis([0 Z_max_])  " << endl
        << "      " << endl
        << "%     axis equal  " << endl
        << "      " << endl
        << "    view([phi theta])  " << endl
        << "    xlabel('X')  " << endl
        << "    ylabel('Y')  " << endl
        << "    zlabel('Density')  " << endl
        << "    str = num2str(i*dt,formatSpec);  " << endl
        << "	title(['Density of the population at time T = ',str])  " << endl
        << "  " << endl
        << "	frame = getframe(figura_);  " << endl
        << "    writeVideo(writerObj,frame);  " << endl
        << "      " << endl
        << "    pause(.1)  " << endl
        << "      " << endl
        << "end  " << endl
        << "  " << endl
        << "  " << endl
        << "close(writerObj);  " << endl
        << "  " << endl
//        << "fprintf('Press a key to continue ...');  " << endl
//        << "input('\\n\\n... ','s');  " << endl
        << "close all  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // function_c.m
    //**************************************************************************************
    
    
    {
        file11 << "function c=function_c(x,t,T,num_funz)  " << endl
        << "% function of the the chemical substance  " << endl
        << "if nargin==0  " << endl
        << "    num_funz=1;  " << endl
        << "    T=100;  " << endl
        << "    t=0;  " << endl
        << "end  " << endl
        << "  " << endl
        << "%% Funzione c(.,.)  " << endl
        << "  " << endl
        << "switch num_funz  " << endl
        << "      " << endl
        << "    case 1  " << endl
        << "        %% SOMBRERO ONDEGGIANTE  " << endl
        << "        T=T/2;  " << endl
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl
        << "        c = 1+6*abs((1+(t-1)/T).*sin(R+2*(t-1)/T)./(R+2*(t-1)/T));  " << endl
        << "      " << endl
        << "      " << endl
        << "    case 2  " << endl
        << "        %% GAUSSIAN  " << endl
        << "        sigma=100;  " << endl
        << "          " << endl
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl
        << "        c = 1+6*exp(-R.^2/sigma);  " << endl
        << "      " << endl
        << "    case 3      " << endl
        << "  " << endl
        << "  " << endl
        << "     c=1+(t<=T)*0+3*(t>T)*(t<=T+1)*(t-T)^2+3*(t>T+1);  " << endl
        << "         " << endl
        << "    case 4  " << endl
        << "        %% CONST>>DECRESCE  " << endl
        << "        c=1+(t<=T)+(t>T)*(t<=T+1)*(t-T-1)^2+(t>T+1)*0;  " << endl
        << "          " << endl
        << "    case 5  " << endl
        << "        %% SUPP COMPATTO GAUSSIANA  " << endl
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl
        << "        c = 1+2*exp(-R.^2/10).*(abs(R)<=5);  " << endl
        << "      " << endl
        << "    case 6  " << endl
        << "        %% CONST>> CRESC. DECRESC.  " << endl
        << "        T=2*T;  " << endl
        << "        c=1+(t<T/3)*0+(t>=T/3)*(t<2*T/3)+(t>2*T/3)*0;  " << endl
        << "          " << endl
        << "    case 7  " << endl
        << "        sigma=5;  " << endl
        << "        R = sqrt(x(1,:).^2 + x(2,:).^2) + eps;  " << endl
        << "        c = 1 + 3*exp(-R.^2/sigma).*(R<=5)+(R>5).*(R<=20).*(.2/10.*(R-5)+.2)+.5246*exp(-(R-40).^2/sigma).*(R>20)+.5*(R>20);  " << endl
        << "          " << endl
        << "end  " << endl
        << "  " << endl
        << "  " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // MovieCpp2matlab.m
    //**************************************************************************************
    
    
    {
        file12 << "function MovieCpp2matlab(n,m)  " << endl
        << "  " << endl
        << "clc  " << endl
        << "  " << endl
        << "%% Caricamento Dati  " << endl
        << "  " << endl
        << "fprintf('---------- CINE-ECOLI-----------\\n\\n')  " << endl
        << "  " << endl
        << " " << endl
        << "    nome = sprintf('Call_Matlab%d-sim-%03d.txt', n,m);" << endl
        << "    Call_Matlab = importdata(nome);" << endl
        << "    fprintf('\\nLoading') " << endl
        << "    X = Call_Matlab.textdata{1}; " << endl
        << "    X=load(X);  " << endl
        << "    indice = Call_Matlab.textdata{2}; " << endl
        << "    indice=load(indice); " << endl
        << "    fprintf('\\n\\nLoading files terminato ... \\n\\n') " << endl
        << "    carat_tecniche = Call_Matlab.data; " << endl
        << "pause(1)  " << endl
        << "clc  " << endl
        << "  " << endl
        << "%% Visualizzazione informazioni relative alla Simulazione  " << endl
        << "  " << endl
        << "fprintf('----------- CINE-ECOLI -------------\\n\\n')  " << endl
        << "      " << endl
        << " informazioni = Call_Matlab.textdata; " << endl
        << "  " << endl
        << "    for i=1:length(informazioni)  " << endl
        << "        fprintf('%s\\n',informazioni{i})  " << endl
        << "    end  " << endl
        << "          " << endl
        << "    fprintf('\\n\\n')  " << endl
        << "  " << endl
        << "	fprintf('Press a key to continue ...');  " << endl
//        << "    getkey;  " << endl
        << "      " << endl
        << "    clc  " << endl
        << "%    fprintf('--------- RUBERESTI MAI UNA AUTO? -----------\\n\\n')  " << endl
        << "%    fprintf('\\n\\n       ...Loading Film...\\n\\n')  " << endl
        << "%    fprintf('\\n\\n--------- NON COMPRARE DVD PIRATA, ARRRGH --------\\n\\n')  " << endl
        << "      " << endl
        << "    num_funz = carat_tecniche(3) ;  " << endl
        << "      " << endl
        << "    if isnan(num_funz)  " << endl
        << "        num_funz=8;  " << endl
        << "    end  " << endl
        << "  " << endl
        << "    %% Caricamento vettore posizione   " << endl
        << "      " << endl
        << "    P=zeros(2,length(indice)-2,indice(2));  " << endl
        << "  " << endl
        << " n_index=0" << endl
        << "    for i=1:(length(indice)-2)  " << endl
        << "          " << endl
        << "        P(1,i,:)=X(n_index+1:i*indice(2),1);  " << endl
        << "        P(2,i,:)=X(n_index+1:i*indice(2),2);  " << endl
        << "        n_index = i*indice(2);" << endl
        << "    end  " << endl
        << "      " << endl
        << "    %% Max asse Z histogramma  " << endl
        << "  " << endl
        << "  " << endl
        << "    %%  ASSI REGOLATI IN BASE AL MASSIMO ASSOLUTO SIMILE A axis equi  " << endl
        << "    mesh_=[min(min(min(P(:,:,:))))-.1,max(max(max(P(:,:,:))))+.1,min(min(min(P(:,:,:))))-.1,max(max(max(P(:,:,:))))+.1];  " << endl
        << "    divx=floor(sqrt(length(indice)-2));  " << endl
        << "    divy=floor(sqrt(length(indice)-2));  " << endl
        << "  " << endl
        << "    hd=[(mesh_(2)-mesh_(1))/divx (mesh_(2)-mesh_(1))/divy];  " << endl
        << "  " << endl
        << "    %% CARICAMENTO FILMATO  " << endl
        << "      " << endl
        << "    fig=1;  " << endl
        << "    [D,a,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd,mesh_,indice(2)...  " << endl
        << "        -indice(1));  " << endl
        << "      " << endl
        << "    fprintf('Max Z Global = %f',Z_max_)  " << endl
        << "    fprintf('\\nMax Z at the end of the simulation: Z(T_f) = %f',Z_max_fin)  " << endl
        << "    fprintf('\\nNow Z is set as Z(max)  = 40')          " << endl
//        << "    ac=input('\\nSet Z max: ','s');  " << endl
        << "  " << endl
//        << "    if ~isnan(str2long double(ac))   " << endl
//        << "        Z_max_ = str2long double(ac);  " << endl
//        << "    else  " << endl
        << "        Z_max_ = 40;  " << endl
//        << "    end  " << endl
        << "    close all  " << endl
        << "    clc  " << endl
        << "      " << endl
        << "    Filmatohist(a,D,mesh_,carat_tecniche(2),indice(2),...  " << endl
        << "        fig,num_funz,informazioni,Z_max_, carat_tecniche);  " << endl
        << "  " << endl
        << "  " << endl
        << "    %% VO AVANTI  " << endl
        << "  " << endl
        << "    fprintf('----------------------------------------\\n\\n')  " << endl
        << "  " << endl
        << "    clc  " << endl
        << "      " << endl
//        << "    fprintf('Press a key to continue ...');  " << endl
//        << "    input('\\n\\n... ','s');  " << endl
        << "    close all  " << endl
        << "      " << endl
        << "    clc  " << endl
        << "      " << endl
//        << "    reply = input('Replay the Film with a different mesh and/or view ?  y/n: ','s');  " << endl
        << "    close all  " << endl
        << "      " << endl
//        << "    %% REPLICHE 2  " << endl
//        << "      " << endl
//        << "    while(reply=='y')  " << endl
//        << "          " << endl
//        << "        clc  " << endl
//        << "        fattore_mesh = input('Which step to be applied to the mesh?  ','s');  " << endl
//        << "      " << endl
//        << "         %% RIFINISCO LA GRIGLIA  " << endl
//        << "        if ~isnan(str2long double(fattore_mesh))   " << endl
//        << "            fattore_mesh = str2long double(fattore_mesh);  " << endl
//        << "        else  " << endl
//        << "            fattore_mesh=1;  " << endl
//        << "        end  " << endl
//        << "          " << endl
//        << "        [D,a,Z_max_,Z_max_fin] = Caricamento_filmato_hist(P,hd*fattore_mesh,mesh_,indice(2)-indice(1));  " << endl
//        << "      " << endl
//        << "        fprintf('Max Z Global = %f',Z_max_)  " << endl
//        << "        fprintf('\\nMax Z at the end of the simulation: Z(T_f) = %f',Z_max_fin)  " << endl
//        << "        fprintf('\\nNow Z is set as Z(max)  = 40')          " << endl
//        << "        ac=input('\\nSet Z max: ','s');  " << endl
//        << "  " << endl
//        << "          " << endl
//        << "  " << endl
//        << "  " << endl
//        << "        if ~isnan(str2long double(ac))   " << endl
//        << "            Z_max_ = str2long double(ac);  " << endl
//        << "        else  " << endl
//        << "            Z_max_ = 40;  " << endl
//        << "        end  " << endl
//        << "        close all  " << endl
//        << "        clc  " << endl
//        << "        Filmatohist(a,D,mesh_,carat_tecniche(2),indice(2),fig,num_funz,informazioni,Z_max_, carat_tecniche);  " << endl
//        << "        clc  " << endl
//        << "        fprintf('Press a key to continue ...');  " << endl
//        << "        input('\\n\\n... ','s');  " << endl
//        << "        close all  " << endl
//        << "        clc   " << endl
//        << "        reply = input('Replay the Film with a different mesh and/or view ?  y/n: ','s');  " << endl
//        << "           " << endl
//        << "    end      " << endl
//        << "      " << endl
        << "    clc  " << endl
//        << "    reply = input('Save the film in .avi format?  y/n: ','s');  " << endl
//        << "  " << endl
        << "  reply = 'y'" << endl
        << "    if reply=='y'  " << endl
        << "  " << endl
        << "        Save_Movie_avi(a,D,mesh_,carat_tecniche(2),indice(2),fig,...  " << endl
        << "                num_funz,informazioni,Z_max_,carat_tecniche,hd,m)     " << endl
        << "    end  " << endl
        << "      " << endl
        << "    clc  " << endl
        << "      " << endl
        << "    Evolution_Mass_center(P,indice(2))  " << endl
        << "      " << endl
        << "    fprintf('Press a key to continue ...');  " << endl
//        << "    getkey;  " << endl
        << "      " << endl
        << "    close;  " << endl
        << "    clc  " << endl
        << "          " << endl
        << "    %% SALVATAGGIO DATI C++  " << endl
//        << "      " << endl
//        << "    reply = input('Save data of the c++ program y/n: ','s');  " << endl
//        << "  " << endl
//        << "    if (reply=='y')  " << endl
//        << "  " << endl
//        << "        clear b_1 b_2 ans salvataggio_ reply hd i j reply P X Y Nx DX DY   " << endl
//        << "        clear mesh1_ D Z_max_ a divx divy fig mesh_ no_conc num_funz  " << endl
//        << "        clear T ans n num_tra salvataggio_ t fattore_mesh dt  " << endl
//        << "        clear C_T C_T_media M M_C salti ac Z_max_fin  " << endl
//        << "        clear delta_C_media lambda_path sciopero rif_temp theta_T  " << endl
//        << "        clear MsupC_T MsupdeltaC MsupJump Msuplambda MsupP Msuptheta  " << endl
//        << "  " << endl
//        << "  " << endl
//        << "        ora_salvataggio=round(clock);  " << endl
//        << "        fprintf('\\nSAVING DATA\\n')  " << endl
//        << "        matFilename = sprintf('Cpp_SDE_STEV_Data_%d_%d_%d_ore%dh%dm.mat',ora_salvataggio(1),ora_salvataggio(2),ora_salvataggio(3),ora_salvataggio(4),ora_salvataggio(5));  " << endl
//        << "        clear ora_salvataggio  " << endl
//        << "        save(matFilename);  " << endl
//        << "          " << endl
//        << "%        delete('/Users/stefanobelloni/Documents/MATLAB/CTRW_Model_Memory/SDE_Towards_Realism_1.8/*.txt');  " << endl
//        << "  " << endl
//        << "          " << endl
//        << "    end  " << endl
        << "  " << endl
        << "      " << endl
        << "distribuzione_tempi(3,n,m); " << endl
        << "distribuzione_tempi(4,n,m);  " << endl
        << "  " << endl
        << "  " << endl
        << "clc  " << endl
        << "clf  " << endl
        << "close all  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // distribuzione_tempi.m
    //**************************************************************************************
    
    
    {
        file13 << "function distribuzione_tempi(n_file,n,cont_sim) " << endl
        << "  " << endl
        << "% Il programma elabora le statischire riguardanti i tempi di salto  " << endl
        << "  " << endl
        << "  " << endl
        << "fprintf('\\nCaricamento dati relativi ai salti ... \\n')  " << endl
        << "nome = sprintf('Call_Matlab%d-sim-%03d.txt', n,cont_sim);" << endl
        << "Call_Matlab = importdata(nome); " << endl
        << "tau=Call_Matlab.textdata{n_file}; " << endl
        << "tau=load(tau);  " << endl
        << "if (n_file==4)"
        << "x_max=1.2;" << endl
        << "else" << endl
        << "x_max=6;" << endl
        << "end " << endl
        << "x=0:.01:2*x_max;  " << endl
        << "  " << endl
        << "  " << endl
        << "R=tau(:,2);  " << endl
        << "n=length(R);  " << endl
        << "  " << endl
        << "figure(1)  " << endl
        << "  " << endl
        << "hist(R,sqrt(n))  " << endl
        << "xlim([0 x_max]) " << endl
        << "fprintf('\\nPress a key to continue ... \\n')  " << endl
        << "  " << endl
//        << "getkey;  " << endl
        << "  " << endl
        << "  " << endl
        << "beta=mean(R);  " << endl
        << "clc  " << endl
        << "fprintf('The measured mean: %f', beta); " << endl
        << "fprintf('\\nThe measured variance: %f', var(R)); " << endl
        << "fprintf('\\nThe std: %f\\n\\n', std(R)); " << endl
        << "  " << endl
        << "fprintf('\\nCreation matrix and elaboration ... \\n')  " << endl
        << "  " << endl
        //        << "f_exp = makedist('Exponential','mu',beta);  " << endl
        //        << "R_exp=random(f_exp,n,1);  " << endl
        //        << "  " << endl
        //        << "A_E=zeros(length(x),1);  " << endl
        //        << "  " << endl
        //        << "for i=1:length(x)  " << endl
        //        << "A_E(i)=sum(R_exp>x(i));  " << endl
        //        << "end  " << endl
        //        << "  " << endl
        //        << "  " << endl
        << "A=zeros(length(x),1);  " << endl
        << "  " << endl
        << "for i=1:length(x)  " << endl
        << "A(i)=sum(R>x(i));  " << endl
        << "end  " << endl
        << "  " << endl
        << "clc  " << endl
        << "fprintf('The measured mean: %f', beta); " << endl
        << "fprintf('\\nThe measured variance: %f', var(R)); " << endl
        << "fprintf('\\nThe std: %f\\n\\n', std(R)); " << endl
        << "  " << endl
        << "figure(2)  " << endl
        << "  " << endl
        << "plot(x,A/n,x,exp(-x/beta)); set(gca,'yscale','log')  " << endl
        << "xlim([0 x_max]) " << endl
        << "legend('Simulated','Exponential')  " << endl
        << "xlabel('run lengths')  " << endl
        << "ylabel('Fraction of runs of a given length')  " << endl
        << "  " << endl
        << "fprintf('\\nPress a key to continue ... \\n')  " << endl
        << "  " << endl
//        << "getkey;  " << endl
        << "  " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    //**************************************************************************************
    // getkey.m
    //**************************************************************************************
    
    
    {
        file14 << "function ch = getkey(m)   " << endl
        << "  " << endl
        << "% GETKEY - get a single keypress  " << endl
        << "%   CH = GETKEY waits for a keypress and returns the ASCII code. Accepts  " << endl
        << "%   all ascii characters, including backspace (8), space (32), enter (13),  " << endl
        << "%   etc, that can be typed on the keyboard. Non-ascii keys (ctrl, alt, ..)  " << endl
        << "%   return a NaN. CH is a long double.   " << endl
        << "%  " << endl
        << "%   CH = GETKEY('non-ascii') uses non-documented matlab features to return  " << endl
        << "%   a string describing the key pressed. In this way keys like ctrl, alt,  " << endl
        << "%   tab etc. can also distinguished. CH is a string.  " << endl
        << "%  " << endl
        << "%   This function is kind of a workaround for getch in C. It uses a modal,  " << endl
        << "%   but non-visible window, which does show up in the taskbar.  " << endl
        << "%   C-language keywords: KBHIT, KEYPRESS, GETKEY, GETCH  " << endl
        << "%  " << endl
        << "%   Examples:  " << endl
        << "%  " << endl
        << "%    fprintf('\\nPress any key: ') ;  " << endl
        << "%    ch = getkey ;  " << endl
        << "%    fprintf('%c\\n',ch) ;  " << endl
        << "%  " << endl
        << "%    fprintf('\\nPress the Ctrl-key: ') ;  " << endl
        << "%    if strcmp(getkey('non-ascii'),'control'),  " << endl
        << "%      fprintf('OK\\n') ;  " << endl
        << "%    else  " << endl
        << "%      fprintf(' ... wrong key ...\\n') ;  " << endl
        << "%    end  " << endl
        << "%  " << endl
        << "%  See also INPUT, UIWAIT  " << endl
        << "%           GETKEYWAIT (File Exchange)  " << endl
        << "  " << endl
        << "% for Matlab 6.5 and higher  " << endl
        << "% version 1.3 (jan 2012)  " << endl
        << "% author : Jos van der Geest  " << endl
        << "% email  : jos@jasen.nl  " << endl
        << "%  " << endl
        << "% History  " << endl
        << "% 2005 - creation  " << endl
        << "% dec 2006 - modified lay-out and help  " << endl
        << "% apr 2009 - tested for more recent MatLab releases   " << endl
        << "% jan 2012 - modified a few properties, included check is figure still  " << endl
        << "%            exists (after comment on FEX by Andrew).  " << endl
        << "  " << endl
        << "% Determine the callback string to use  " << endl
        << "if nargin == 1,  " << endl
        << "    if strcmpi(m,'non-ascii'),  " << endl
        << "        callstr = 'set(gcbf,''Userdata'',get(gcbf,''Currentkey'')) ; uiresume ' ;  " << endl
        << "    else         " << endl
        << "        error('Argument should be the string ''non-ascii''') ;  " << endl
        << "    end  " << endl
        << "else  " << endl
        << "    callstr = 'set(gcbf,''Userdata'',long double(get(gcbf,''Currentcharacter''))) ; uiresume ' ;  " << endl
        << "end  " << endl
        << "  " << endl
        << "% Set up the figure  " << endl
        << "% May be the position property  should be individually tweaked to avoid visibility  " << endl
        << "fh = figure(...  " << endl
        << "    'name','Press a key', ...  " << endl
        << "    'keypressfcn',callstr, ...  " << endl
        << "    'windowstyle','modal',...   " << endl
        << "    'numbertitle','off', ...  " << endl
        << "    'position',[0 0  1 1],...  " << endl
        << "    'userdata','timeout') ;   " << endl
        << "try  " << endl
        << "    % Wait for something to happen  " << endl
        << "    uiwait ;  " << endl
        << "    ch = get(fh,'Userdata') ;  " << endl
        << "    if isempty(ch),  " << endl
        << "        ch = NaN ;   " << endl
        << "    end  " << endl
        << "catch  " << endl
        << "    % Something went wrong, return and empty matrix.  " << endl
        << "    ch = [] ;  " << endl
        << "end  " << endl
        << "  " << endl
        << "if ishandle(fh)  " << endl
        << "    delete(fh) ;  " << endl
        << "end  " << endl
        << "  " << endl
        << " " << endl
        << " " << endl;
    }
    
    
    //**************************************************************************************
    
    
    
    
}
