import { Control } from "react-hook-form";

export interface InputType {
  label: string;
  unit?: string;
  type: "field" | "dropdown" | "upload" | "field-upload";
  name: string;
  placeholder?: string;
  isReadOnly?: boolean;
  options?: string[]; // For dropdown
  requiredColumns?: number; // For CSV upload
}

export interface InputWidgetProps {
  inputType: InputType;
  control: Control<any>;
  onFileLoad?: (name: string, data: number[][]) => void;
}

export interface InputFieldProps {
  label: string;
  unit?: string;
  name: string;
  placeholder?: string;
  isReadOnly?: boolean;
  control: Control<any>;
}

export interface InputDropdownProps {
  label: string;
  name: string;
  options: string[];
  value?: string | number;
  control: Control<any>;
}

export interface InputUploadProps {
  label?: string;
  name: string;
  requiredColumns?: number;
  control: Control<any>;
  onFileLoad?: (filePath: string, data: number[][]) => void;
}

export interface InputFieldUploadProps {
  label: string;
  unit?: string;
  name: string;
  value?: number;
  requiredColumns?: number;
  placeholder?: string;
  isReadOnly?: boolean;
  onFieldChange?: (value: number) => void;
  onFileLoad?: (filePath: string, data: number[][]) => void;
  onError?: (error: string) => void;
}
